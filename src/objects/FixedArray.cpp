//
// Created by anarion on 7/23/20.
//

#include "objects/FixedArray.h"
#include <page/PageManager.h>

anarion::FixedArray::FixedArray(PageManager &manager, SString &&name, size_type elementLength)
        : PageMappedObject(manager, forward<SString>(name)), elementLength(elementLength), freeSpaceManager(10) {

}

void anarion::FixedArray::computeElementIndices(anarion::size_type elementIndex, anarion::size_type *pageIndex, anarion::size_type *pageOffset) const {
    size_type pageLength = manager.getPageLength();
    size_type byteIndex = elementIndex * elementLength;
    *pageIndex = byteIndex / pageLength;
    *pageOffset = byteIndex % pageLength;
    *pageOffset = pageLength - *pageOffset;
}

void anarion::FixedArray::insert(const char *data) {
    size_type targetIndex = freeSpaceManager.getFree(), pageIndex, pageOffset;
    computeElementIndices(targetIndex, &pageIndex, &pageOffset);
    write(pageIndex, pageOffset, data, elementLength);
}

void anarion::FixedArray::fetch(char *data, anarion::size_type index) {
    size_type pageIndex, pageOffset;
    computeElementIndices(index, &pageIndex, &pageOffset);
    read(pageIndex, pageOffset, data, elementLength);
}

void anarion::FixedArray::update(const char *data, anarion::size_type index) {
    size_type pageIndex, pageOffset;
    computeElementIndices(index, &pageIndex, &pageOffset);
    write(pageIndex, pageOffset, data, elementLength);
}

void anarion::FixedArray::remove(anarion::size_type index) {
    freeSpaceManager.setFree(index);
}
