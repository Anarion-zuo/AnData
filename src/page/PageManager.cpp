//
// Created by anarion on 7/12/20.
//

#include "page/PageManager.h"
#include <container/SString.h>
#include <cstdlib>

void anarion::PageManager::constructor(size_type pageLength, size_type pageCount) {
    this->pageLength = pageLength;
    this->pageCount = pageCount;
    size_type byteCount = getByteCount();

    // initialize @pageSpace to be all 0
    pageSpace = static_cast<char *>(operator new(byteCount));
    bzero(pageSpace, byteCount);

    // initialize $pageInfo to be all 0
    pageInfo = static_cast<PageInfo *>(operator new(pageCount * sizeof(PageInfo)));
    bzero(pageInfo, pageCount * sizeof(PageInfo));

    // evicting mechanism implementation
    evictScanner._this = this;
    usageBitMap.resize(pageCount);

    // initialize dirty bit
    pagesDirty.resize(pageCount);

    // open the directory and all files under it
    directory.open();
}

void anarion::PageManager::EvictScanner::task() {
    unsigned char *usageBitMap = _this->usageBitMap.getArr();
    size_type bitMapCharLength = _this->usageBitMap.getCharLength();
    for (size_type arrayIndex = 0; arrayIndex < bitMapCharLength; ++arrayIndex) {
        unsigned char &charSeg = usageBitMap[arrayIndex];
        if (charSeg != 0xff) {
            for (size_type bitIndex = 0; bitIndex < 8; ++bitIndex) {
                if (!(charSeg & (1u << bitIndex))) {
                    size_type res = arrayIndex * 8 + bitIndex;
                    if (res < _this->pageCount) {
                        _this->evictCandidateIndex = res;
                        return;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    // all pages are used in this short while
    _this->evictCandidateIndex = rand() / _this->pageCount;
}

void anarion::PageManager::getPage(PageMappedObject *object, anarion::size_type objIndex) {
    const anarion::SString &objName = object->getName();
    // find the obj directory, create if not found
    FileEntry *dirEntry = directory.getChild(objName);
    if (dirEntry == nullptr) {
        dirEntry = directory.createChildDirectory(SString(objName));
    } else {
        // name exists as a file
        if (dirEntry->isFile()) {
            throw PageFileExistsException();
        }
    }
    Directory *dir = dynamic_cast<Directory *>(dirEntry);
    // find the page file
    SString indexString = SString::parseDec(objIndex);
    FileEntry *fileEntry = dirEntry->getChild(indexString);
    // create empty file if not found
    if (fileEntry == nullptr) {
        dir->createChildFile(indexString);
    }
    size_type evictingIndex = evictCandidateIndex;
    PageInfo &info = pageInfo[evictingIndex];
    // check if the page is occupied
    if (info.setPointer) {
        // assigned to another object
        // find the page file & directory
        SString evictedIndexString = SString::parseDec(info.setIndex);
        Directory *evictingDirectory = dynamic_cast<Directory *>(directory.getChild(info.setPointer->getName()));
        // create directory if not exists
        if (evictingDirectory == nullptr) {
            evictingDirectory = dynamic_cast<Directory *>(directory.createChildDirectory(SString(info.setPointer->getName())));
        }
        FileEntry *evictingFile = evictingDirectory->getChild(evictedIndexString);
        // create file if not exists
        if (evictingFile == nullptr) {
            evictingFile = evictingDirectory->createChildFile(evictedIndexString);
        }
        FileChannel *file = dynamic_cast<FileChannel *>(evictingFile);
        // unload handled by dedicated method
        unloadPage(*file, evictingIndex);
    }
    // prepare space, load or bzero
    // get page head by index
    char *pageHead = getPageHeadByIndex(evictingIndex);
    if (fileEntry == nullptr) {
        // present zero page if the page is not on disk
        bzero(pageHead, pageLength);
        // must sync at least zero page to disk, therefore setting dirty bit
        pagesDirty.set(evictingIndex);
    } else {
        // load the file if the page is on disk
        FileChannel *file = dynamic_cast<FileChannel *>(fileEntry);
        file->out(pageHead, pageLength);
        // might not write to this page, therefore clearing dirty bit
        pagesDirty.clear(evictingIndex);
    }
    // refresh page info
    pageInfo->setPointer = object;
    pageInfo->setIndex = objIndex;
    // load page into the object
    object->setPage(objIndex, evictingIndex);
}

void anarion::PageManager::setUsageBitMap(anarion::size_type index) {
    usageBitMap.set(index);
}

void anarion::PageManager::unloadPage(anarion::FileChannel &file, anarion::size_type pageIndex) {
    // must sync to files if dirty
    if (pagesDirty.check(pageIndex)) {
        file.rewind();
        file.in(getPageHeadByIndex(pageIndex), pageLength);
        pagesDirty.clear(pageIndex);
    }
    // remove from object if belongs to an object
    pageInfo[pageIndex].setPointer->setPageNull(pageInfo[pageIndex].setIndex);
    // reset page info
    bzero(pageInfo + pageIndex, sizeof(PageInfo));
}

void anarion::PageManager::setDirtyBit(anarion::size_type index) {
    pagesDirty.set(index);
}

anarion::size_type
anarion::PageManager::writePage(anarion::size_type pageIndex, anarion::size_type offset, const char *data, anarion::size_type dataLength) {
    // find page head pointer
    char *pageHead = getPageHeadByIndex(pageIndex);
    size_type retLength;
    // compute length
    if (pageLength > offset + dataLength) {
        retLength = dataLength;
    } else {
        retLength = dataLength - (pageLength - offset);
    }
    // perform write
    memcpy(pageHead + offset, data, retLength);
    // set dirty bit
    pagesDirty.set(pageIndex);
    return retLength;
}

anarion::size_type anarion::PageManager::readPage(anarion::size_type pageIndex, anarion::size_type offset, char *data, anarion::size_type dataLength) const {
    // find page head pointer
    char *pageHead = getPageHeadByIndex(pageIndex);
    size_type retLength;
    // compute length
    if (pageLength > offset + dataLength) {
        retLength = dataLength;
    } else {
        retLength = dataLength - (pageLength - offset);
    }
    // perform read
    memcpy(data, pageHead + offset, retLength);
    return retLength;
}

anarion::PageManager::~PageManager() {
//    directory.close();
    operator delete (pageInfo, pageCount * sizeof(PageInfo));
    operator delete(pageSpace, getByteCount());
}

void anarion::PageManager::unloadAll() {
    for (size_type index = 0; index < pageCount; ++index) {
        PageInfo &info = pageInfo[index];
        if (info.setPointer == nullptr) {
            continue;
        }
        if (info.setPointer->isPageNull(info.setIndex)) {
            continue;
        }
        const SString &dirName = info.setPointer->getName();
        Directory *dir = dynamic_cast<Directory *>(directory.getChild(dirName));
        if (dir == nullptr) {
            dir = dynamic_cast<Directory *>(directory.createChildDirectory(SString(dirName)));
        }
        SString fileName = SString::parseDec(info.setIndex);
        FileChannel *file = dynamic_cast<FileChannel *>(dir->getChild(fileName));
        if (file == nullptr) {
            file = dynamic_cast<FileChannel *>(dir->createChildFile(SString(fileName)));
        }
        unloadPage(*file, index);
    }
}
