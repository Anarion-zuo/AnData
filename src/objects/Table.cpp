//
// Created by anarion on 7/24/20.
//

#include <objects/column/FixedLengthColumn.h>
#include "objects/table/Table.h"

anarion::Table::Table(Directory &directory, SString &&name, size_type pageLength, size_type pageCount)
    : pageManager(directory, pageLength, pageCount), name(forward<SString>(name)), freeSpaceManager(initSlotCount) {

}

anarion::Table::~Table() {
    // must first unload then delete memory instances, or data might be lost
    pageManager.unloadAll();
    for (size_type index = 0; index < columns.size(); ++index) {
        delete columns.get(index);
    }
}

anarion::ColumnInterface *anarion::Table::makeColumn(anarion::SString &&colName, anarion::size_type elementLength) {
    return new FixedLengthColumn(pageManager, forward<SString>(colName), elementLength);
}

anarion::size_type anarion::Table::getFreeIndex() {
    size_type ret = freeSpaceManager.getFree();
    if (ret == -1) {
        freeSpaceManager.resize(freeSpaceManager.getSlotCount() * 2 + 1);
        ret = freeSpaceManager.getFree();
    }
    return ret;
}

anarion::size_type anarion::Table::insert(anarion::size_type colIndex, const char *data) {
    size_type targetIndex = getFreeIndex();
    columns.get(colIndex)->insert(data, targetIndex);
    return targetIndex;
}

void anarion::Table::fetch(size_type colIndex, size_type rowIndex, char *data) {
    columns.get(colIndex)->fetch(data, rowIndex);
}

void anarion::Table::update(anarion::size_type colIndex, size_type rowIndex, const char *data) {
    columns.get(colIndex)->update(data, rowIndex);
}

void anarion::Table::remove(size_type colIndex, anarion::size_type rowIndex) {
    columns.get(colIndex)->remove(rowIndex);
}

void anarion::Table::appendColumn(SString &&colName, anarion::size_type elementLength) {
    name2ColIndex.insert({colName, columns.size()});
    ColumnInterface *newCol = makeColumn(forward<SString>(colName), elementLength);
    columns.push_back(newCol);
}
