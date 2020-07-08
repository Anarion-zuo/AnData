//
// Created by 左钰 on 2020/5/30.
//

#ifndef ANDATA_MATRIX_H
#define ANDATA_MATRIX_H

#include "Array.h"

namespace anarion {
    struct MatrixException : public std::exception {};
    struct MatrixShapeNotMatch : public MatrixException {};

    class Matrix {
    protected:
        Vector<ArrayInterface*> columns;
    public:
        Matrix() = default;
        Matrix(const Matrix &rhs);
        Matrix(Matrix &&rhs) noexcept = default;
        ~Matrix();
        Matrix &operator=(const Matrix &);
        Matrix &operator=(Matrix &&) noexcept = default;

        Matrix(std::initializer_list<ArrayInterface*> &&initList)
            : columns(anarion::forward<std::initializer_list<ArrayInterface*>>(initList)) {}

        uint64 getInteger(size_type rowIndex, size_type colIndex);
        float64 getFloat(size_type rowIndex, size_type colIndex);

        size_type getWidth() const ;
        size_type getHeight() const ;

        bool isInteger() const ;

        ArrayInterface *getColumn(size_type index);
        ArrayInterface *getRow(size_type index);

        // structural
        void push_back(const ArrayInterface &rhs);
    };
}

#endif //ANDATA_MATRIX_H
