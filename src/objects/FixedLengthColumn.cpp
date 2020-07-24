//
// Created by anarion on 7/23/20.
//

#include "objects/column/FixedLengthColumn.h"
#include <page/PageManager.h>

anarion::FixedLengthColumn::FixedLengthColumn(PageManager &manager, SString &&name, size_type elementLength)
        : ColumnInterface(manager, forward<SString>(name)), elementLength(elementLength) {

}

void anarion::FixedLengthColumn::computeElementIndices(anarion::size_type elementIndex, anarion::size_type *pageIndex, anarion::size_type *pageOffset) const {
    size_type pageLength = manager.getPageLength();
    size_type byteIndex = elementIndex * elementLength;
    *pageIndex = byteIndex / pageLength;
    *pageOffset = byteIndex % pageLength;
    *pageOffset = pageLength - *pageOffset - elementLength;
}

void anarion::FixedLengthColumn::insert(const char *data, size_type targetIndex) {
    size_type pageIndex, pageOffset;
    computeElementIndices(targetIndex, &pageIndex, &pageOffset);
    write(pageIndex, pageOffset, data, elementLength);
    ++elementCount;
}

void anarion::FixedLengthColumn::fetch(char *data, anarion::size_type index) {
    size_type pageIndex, pageOffset;
    computeElementIndices(index, &pageIndex, &pageOffset);
    read(pageIndex, pageOffset, data, elementLength);
}

void anarion::FixedLengthColumn::update(const char *data, anarion::size_type index) {
    size_type pageIndex, pageOffset;
    computeElementIndices(index, &pageIndex, &pageOffset);
    write(pageIndex, pageOffset, data, elementLength);
}

void anarion::FixedLengthColumn::remove(anarion::size_type index) {
    --elementCount;
}
