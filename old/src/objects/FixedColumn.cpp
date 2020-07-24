//
// Created by anarion on 6/23/20.
//

#include "objects/FixedColumn.h"

anarion::FixedColumn::FixedColumn(anarion::PageManager &pageManager, anarion::size_type itemLength, anarion::size_type itemCount)
    : pageManager(pageManager), itemLength(itemLength), itemCount(itemCount) {
    size_type byteCount = itemLength * itemCount;
    pageCount = byteCount / pageManager.getFrameLength();
    pages = static_cast<Page **>(operator new(sizeof(void *) * pageCount));
    bzero(pages, pageCount * sizeof(void*));
}

void anarion::FixedColumn::getByIndex(anarion::size_type index, char *buf) const {
    pageManager.load(<#initializer#>, 0, 0)
}
