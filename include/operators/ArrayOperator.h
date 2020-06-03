//
// Created by 左钰 on 2020/5/31.
//

#ifndef ANDATA_ARRAYOPERATOR_H
#define ANDATA_ARRAYOPERATOR_H

#include <series/Array.h>

namespace anarion {
    class ArrayOperator {
    protected:

    public:
        ArrayInterface *concat(const Vector<ArrayInterface *> &arrays);

        ArrayInterface *add(const ArrayInterface &x, const ArrayInterface &y);
        ArrayInterface *sub(const ArrayInterface &x, const ArrayInterface &y);
        ArrayInterface *mul(const ArrayInterface &x, const ArrayInterface &y);
        ArrayInterface *div(const ArrayInterface &x, const ArrayInterface &y);

        float64 sum(const ArrayInterface &array);
        float64 mean(const ArrayInterface &array);
        float64 powerSum(const ArrayInterface &array, size_type n_power);
        float64 powerSum(const ArrayInterface &array, float64 n_power);
        float64 variance(const ArrayInterface &array);
        float64 stdVariance(const ArrayInterface &array);

        ArrayInterface * centralize(ArrayInterface &array);
        ArrayInterface * standardize(ArrayInterface &array);
    };
}

#endif //ANDATA_ARRAYOPERATOR_H
