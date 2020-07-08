//
// Created by anarion on 6/24/20.
//

#include "operators/MatrixOperator.h"

anarion::ArrayInterface *anarion::MatrixOperator::dot(anarion::Matrix &matrix, anarion::ArrayInterface &array) {
    if (matrix.getWidth() != array.length()) {
        throw ArraySizeNotMatch();
    }
    size_type retLength = matrix.getHeight();
    ArrayInterface *ret = new BigFloatArray(retLength);
    for (size_type rowIndex = 0; rowIndex < retLength; ++rowIndex) {
        float64 entry = 0;
        for (size_type colIndex = 0; colIndex < array.length(); ++colIndex) {
            entry += array.getFloat(rowIndex) * matrix.getFloat(rowIndex, colIndex);
        }
        ret->push_back(entry);
    }
    return ret;
}

anarion::float64
anarion::MatrixOperator::dot(anarion::Matrix &matrix, anarion::size_type rowIndex, anarion::ArrayInterface &array) {
    if (matrix.getWidth() != array.length()) {
        throw ArraySizeNotMatch();
    }
    float64 ret = 0;
    for (size_type colIndex = 0; colIndex < array.length(); ++colIndex) {
        ret += matrix.getFloat(rowIndex, colIndex) * array.getFloat(colIndex);
    }
    return ret;
}
