//
// Created by anarion on 7/8/20.
//

#include "page/PageManager.h"
#include <container/StringBuilder.h>
#include <io/channel/file/FileChannel.h>

void anarion::PageManager::initializeFrameSpace() {
    // frame space
    pageByteCount = pageMaxNumber * pageLength;
    pageHead = static_cast<char *>(operator new(pageByteCount));
    directory.open();
    memset(pageHead, 0, pageByteCount);

    // lru array
    size_type flagSegCount = pageMaxNumber / sizeof(long), moreCount = pageMaxNumber % sizeof(long);
    if (moreCount) {
        ++flagSegCount;
    }
    usedFlags = static_cast<long *>(operator new(flagSegCount));
    bzero(usedFlags, flagSegCount * sizeof(long));
    clockSweeper._this = this;
    clockSweeper.start();

    // to objects
    belongedObjects = static_cast<PageMappedObject **>(operator new(sizeof(void *) * pageMaxNumber));
    bzero(belongedObjects, sizeof(void*) * pageMaxNumber);
}

anarion::PageManager::~PageManager() {
    operator delete(pageHead, pageByteCount);
}

anarion::size_type anarion::PageManager::pageIndex2ByteIndex(anarion::size_type frameIndex) const {
    return frameIndex * pageLength;
}

char *anarion::PageManager::getPageHeadByIndex(anarion::size_type frameIndex) const {
    return pageHead + pageIndex2ByteIndex(frameIndex);
}

anarion::Page *anarion::PageManager::load(const SString &objName, size_type objPageIndex, size_type pageIndex) {
    SString fileName = SString::parseDec(objPageIndex);

    FileEntry *dir = directory.getChild(objName);
    if (dir == nullptr) {
        dir = directory.createChildDirectory(SString(objName));
    } else {
        if (dir->isFile()) {
            throw DuplicateObjectNameException();
        }
    }

    FileEntry *entry = dir->getChild(fileName);
    FileChannel *file = dynamic_cast<FileChannel *>(entry);
    if (file) {
        file->rewind();
        file->out(getPageHeadByIndex(pageIndex), pageLength);
    } else {
        zeroPage(pageIndex);
    }
    Page *ret = new Page(getPageHeadByIndex(pageIndex), pageLength, pageIndex);
    return ret;
}

anarion::SString anarion::PageManager::buildFileName(const anarion::SString &colName, anarion::size_type pageIndex) {
    StringBuilder builder;
    builder.cappend(colName);
    builder.cappend("#", 1);
    builder.appendNumber(pageIndex);
    SString fileName = builder.build();
    return fileName;
}

void anarion::PageManager::zeroPage(anarion::size_type frameIndex) {
    bzero(getPageHeadByIndex(frameIndex), pageLength);
}

void anarion::PageManager::unload(anarion::Page *page, const anarion::SString &objName) {
    size_type pageIndex = page->getFrameIndex();
    if (page->checkIsDirty()) {
        Directory *dir = dynamic_cast<Directory *>(directory.getChild(objName));
        SString fileName = SString::parseDec(page->getFrameIndex());
        // try fetch the file from file system
        FileEntry *entry = dir->getChild(fileName);
        FileChannel *file = dynamic_cast<FileChannel *>(entry);
        if (file) {
            file->rewind();
        } else {
            file = dynamic_cast<FileChannel *>(dir->createChildFile(fileName));
        }
        file->in(getPageHeadByIndex(pageIndex), pageLength);
    }
    delete page;
}

anarion::Page *anarion::PageManager::getPageByName(const anarion::PageMappedObject &mappedObj, anarion::size_type index) {

}

anarion::size_type anarion::PageManager::getEvictingIndex() const {
    return evictableIndex;
}

bool anarion::PageManager::getUsedFlag(anarion::size_type index) const {
    size_type arrayIndex = index / sizeof(long), bitIndex = index % sizeof(long);
    return usedFlags[arrayIndex] & (1ul << bitIndex);
}

void anarion::PageManager::setUsedFlag(anarion::size_type index) {
    size_type arrayIndex = index / sizeof(long), bitIndex = index % sizeof(long);
    usedFlags[arrayIndex] |= 1l << bitIndex;
}

void anarion::PageManager::clearUsedFlag(anarion::size_type index) {
    size_type arrayIndex = index / sizeof(long), bitIndex = index % sizeof(long);
    usedFlags[arrayIndex] &= ~(1l << bitIndex);
}

void anarion::PageManager::ClockSweeper::task() {
    if (_this->currentSweepingIndex == _this->pageMaxNumber) {
        _this->currentSweepingIndex = 0;
    }
    if (_this->getUsedFlag(_this->currentSweepingIndex)) {
        _this->clearUsedFlag(_this->currentSweepingIndex);
    } else {
        _this->evictableIndex = _this->currentSweepingIndex;
    }
    ++_this->currentSweepingIndex;
}

