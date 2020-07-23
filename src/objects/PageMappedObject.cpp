//
// Created by anarion on 7/12/20.
//

#include "objects/PageMappedObject.h"
#include <page/PageManager.h>

void anarion::PageMappedObject::setPageNull(size_type index) {
    getPageManagerIndex(index) = manager.getPageCount();
}

bool anarion::PageMappedObject::isPageNull(anarion::size_type index) {
    return getPageManagerIndex(index) == manager.getPageCount();
}

void anarion::PageMappedObject::setPage(anarion::size_type index, size_type managerIndex) {
    getPageManagerIndex(index) = managerIndex;
}

anarion::PageMappedObject::PageMappedObject(anarion::PageManager &manager, anarion::SString &&name)
    : manager(manager), name(forward<SString>(name)) {

}

bool anarion::PageMappedObject::computeIndexes(anarion::size_type byteIndex, anarion::size_type *pageIndex, anarion::size_type *pageOffset) {
    *pageIndex = byteIndex / manager.getPageLength();
    *pageOffset = byteIndex % manager.getPageCount();
    if (*pageOffset == 0 && byteIndex != 0) {
        ++ *pageIndex;
    }
    return *pageIndex >= manager.getPageCount();
}

void anarion::PageMappedObject::write(anarion::size_type beginPageIndex, anarion::size_type beginPageOffset, const char *data, anarion::size_type length) {
    // compute index information and check for overflow
    // ...
    // allocate page
    if (isPageNull(beginPageIndex)) {
        manager.getPage(this, beginPageIndex);
    }
    // perform write
    size_type writtenLength = manager.writePage(getPageManagerIndex(beginPageIndex), beginPageOffset, data, length);
    data += writtenLength;
    length -= writtenLength;
    size_type pageIndex = beginPageIndex + 1, offset = 0;
    while (length) {
        if (isPageNull(pageIndex)) {
            manager.getPage(this, pageIndex);
        }
        writtenLength = manager.writePage(getPageManagerIndex(pageIndex), offset, data, length);
        data += writtenLength;
        length -= writtenLength;
        ++pageIndex;
    }
}

void anarion::PageMappedObject::read(anarion::size_type beginPageIndex, anarion::size_type beginPageOffset, char *data, anarion::size_type length) {
    // compute index information and check for overflow
//    size_type endIndex = byteIndex + length;
//    size_type beginPageIndex, endPageIndex, beginPageOffset, endPageOffset;
//    if (computeIndexes(byteIndex, &beginPageIndex, &beginPageOffset)) {
//        throw IndexOutOfRange();
//    }
//    if (computeIndexes(endIndex, &endPageIndex, &endPageOffset)) {
//        throw IndexOutOfRange();
//    }
    // perform read
    size_type readLength = manager.readPage(beginPageIndex, beginPageOffset, data, length);
    data += readLength;
    length -= readLength;
    size_type pageIndex = beginPageIndex + 1, offset = 0;
    while (length) {
        readLength = manager.readPage(pageIndex, offset, data, length);
        data += readLength;
        length -= readLength;
        ++pageIndex;
    }
}

anarion::size_type &anarion::PageMappedObject::getPageManagerIndex(anarion::size_type pageIndex) {
    if (pageIndex >= pageManagerIndexes.size()) {
        pageManagerIndexes.resize(pageIndex + 1);
        for (size_type i = 0; i <= pageIndex; ++i) {
            pageManagerIndexes.push_back(manager.getPageCount());
        }
    }
    return pageManagerIndexes.get(pageIndex);
}
