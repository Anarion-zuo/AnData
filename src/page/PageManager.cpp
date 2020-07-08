//
// Created by anarion on 7/8/20.
//

#include "page/PageManager.h"
#include <container/StringBuilder.h>
#include <io/channel/file/FileChannel.h>

void anarion::PageManager::initializeFrameSpace() {
    frameByteCount = frameMaxNumber * frameLength;
    frameHead = static_cast<char *>(operator new(frameByteCount));
    directory.open();
    memset(frameHead, 0, frameByteCount);
}

anarion::PageManager::~PageManager() {
    operator delete(frameHead, frameByteCount);
}

anarion::size_type anarion::PageManager::frameIndex2ByteIndex(anarion::size_type frameIndex) const {
    return frameIndex * frameLength;
}

char *anarion::PageManager::getFrameHeadByIndex(anarion::size_type frameIndex) const {
    return frameHead + frameIndex2ByteIndex(frameIndex);
}

anarion::Page *anarion::PageManager::load(const anarion::SString &colName, anarion::size_type pageIndex) {
    // build file name
    SString fileName = buildFileName(colName, pageIndex);

    // try fetch the file from file system
    FileEntry *entry = directory.getChild(fileName);
    FileChannel *file = dynamic_cast<FileChannel *>(entry);
    if (file) {
        file->rewind();
        file->out(getFrameHeadByIndex(pageIndex), frameLength);
    } else {
        zeroFrame(pageIndex);
    }
    return new Page(getFrameHeadByIndex(pageIndex), frameLength, pageIndex);
}

anarion::SString anarion::PageManager::buildFileName(const anarion::SString &colName, anarion::size_type pageIndex) {
    StringBuilder builder;
    builder.cappend(colName);
    builder.cappend("#", 1);
    builder.appendNumber(pageIndex);
    SString fileName = builder.build();
    return fileName;
}

void anarion::PageManager::zeroFrame(anarion::size_type frameIndex) {
    bzero(getFrameHeadByIndex(frameIndex), frameLength);
}

void anarion::PageManager::unload(anarion::Page *page, const anarion::SString &colName) {
    size_type pageIndex = page->getFrameIndex();
    if (page->checkIsDirty()) {
        SString fileName = buildFileName(colName, pageIndex);
        // try fetch the file from file system
        FileEntry *entry = directory.getChild(fileName);
        FileChannel *file = dynamic_cast<FileChannel *>(entry);
        if (file) {
            file->rewind();
        } else {
            file = dynamic_cast<FileChannel *>(directory.createChildFile(fileName));
        }
        file->in(getFrameHeadByIndex(pageIndex), frameLength);
    }
    delete page;
}
