//
// Created by anarion on 6/24/20.
//

#ifndef ANDATA_MATRIXOPERATOR_H
#define ANDATA_MATRIXOPERATOR_H

#include <series/Matrix.h>
#include "ArrayOperator.h"

namespace anarion {
    class MatrixOperator : public ArrayOperator {
    public:
        // dot product between matrix and column vector
        ArrayInterface *dot(Matrix &matrix, ArrayInterface &array);
        // dot product between a row of the matrix and a vector
        float64 dot(Matrix &matrix, size_type rowIndex, ArrayInterface &array);
    };
}

#endif //ANDATA_MATRIXOPERATOR_H
