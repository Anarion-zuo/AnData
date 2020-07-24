//
// Created by anarion on 7/24/20.
//

#include "objects/column/impl/IntegerColumn.h"

anarion::IntegerColumn::IntegerColumn(anarion::PageManager &manager, anarion::SString &&name)
        : FixedLengthColumn(manager, forward<SString>(name), sizeof(int)) {}

void anarion::IntegerColumn::insert(int number, size_type index) {
    FixedLengthColumn::insert(toCharPointer(number), index);
}

int anarion::IntegerColumn::fetch(anarion::size_type index) {
    int ret;
    FixedLengthColumn::fetch(toCharPointer(ret), index);
    return ret;
}

void anarion::IntegerColumn::update(anarion::size_type index, int number) {
    FixedLengthColumn::update(toCharPointer(number), index);
}
