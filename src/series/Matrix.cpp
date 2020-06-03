//
// Created by 左钰 on 2020/5/30.
//

#include "series/Matrix.h"

anarion::Matrix::Matrix(const anarion::Matrix &rhs) : columns(rhs.columns.size()) {
    for (size_type index = 0; index < rhs.columns.size(); ++index) {
        columns.push_back(columns[index]->clone());
    }
}

anarion::Matrix::~Matrix() {
    for (size_type index = 0; index < columns.size(); ++index) {
        delete columns[index];
    }
}

anarion::uint64 anarion::Matrix::getInteger(anarion::size_type rowIndex, anarion::size_type colIndex) {
    return columns[colIndex]->getInteger(rowIndex);
}

anarion::float64 anarion::Matrix::getFloat(anarion::size_type rowIndex, anarion::size_type colIndex) {
    return columns[colIndex]->getFloat(rowIndex);
}

anarion::Matrix &anarion::Matrix::operator=(const anarion::Matrix &rhs) {
    if (&rhs == this) { return *this; }
    // clear old
    for (size_type index = 0; index < columns.size(); ++index) {
        delete columns[index];
    }
    columns.clear();
    columns.resize(rhs.columns.size());
    // inject
    for (size_type index = 0; index < rhs.columns.size(); ++index) {
        columns.push_back(columns[index]->clone());
    }
    return *this;
}

anarion::size_type anarion::Matrix::getWidth() const {
    return columns.size();
}

anarion::size_type anarion::Matrix::getHeight() const {
    if (getWidth() == 0) { return 0; }
    return columns[0]->length();
}

void anarion::Matrix::push_back(const anarion::ArrayInterface &rhs) {
    if (rhs.length() != getWidth()) { throw MatrixShapeNotMatch(); }
    for (size_type index = 0; index < getWidth(); ++index) {
        ArrayInterface *array = columns[index];
        if (array->isInteger()) {
            array->push_back(rhs.getInteger(index));
        } else {
            array->push_back(rhs.getFloat(index));
        }
    }
}
