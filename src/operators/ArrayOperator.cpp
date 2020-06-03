//
// Created by 左钰 on 2020/5/31.
//

#include "operators/ArrayOperator.h"
#include <cmath>

anarion::float64 anarion::ArrayOperator::sum(const anarion::ArrayInterface &array) {
    float64 sum = 0;
    for (size_type index = 0; index < array.length(); ++index) {
        sum += array.getFloat(index);
    }
    return sum;
}

anarion::float64 anarion::ArrayOperator::mean(const anarion::ArrayInterface &array) {
    return sum(array) / array.length();
}

anarion::float64 anarion::ArrayOperator::powerSum(const anarion::ArrayInterface &array, anarion::size_type n_power) {
    float64 sum = 0;
    for (size_type index = 0; index < array.length(); ++index) {
        sum += pow(array.getFloat(index), n_power);
    }
    return sum;
}

anarion::float64 anarion::ArrayOperator::powerSum(const anarion::ArrayInterface &array, anarion::float64 n_power) {
    float64 sum = 0;
    for (size_type index = 0; index < array.length(); ++index) {
        sum += pow(array.getFloat(index), n_power);
    }
    return sum;
}

anarion::float64 anarion::ArrayOperator::variance(const anarion::ArrayInterface &array) {
    float64 meanVal = mean(array), sum = 0;
    for (size_type index = 0; index < array.length(); ++index) {
        sum += pow(array.getFloat(index) - meanVal, 2);
    }
    return sum / (array.length() - 1ul);
}

anarion::float64 anarion::ArrayOperator::stdVariance(const anarion::ArrayInterface &array) {
    return sqrt(variance(array));
}

anarion::ArrayInterface *
anarion::ArrayOperator::add(const anarion::ArrayInterface &x, const anarion::ArrayInterface &y) {
    ArrayInterface *p = x.clone();
    p->add(y);
    return p;
}

anarion::ArrayInterface *
anarion::ArrayOperator::sub(const anarion::ArrayInterface &x, const anarion::ArrayInterface &y) {
    ArrayInterface *p = x.clone();
    p->sub(y);
    return p;
}

anarion::ArrayInterface *
anarion::ArrayOperator::mul(const anarion::ArrayInterface &x, const anarion::ArrayInterface &y) {
    ArrayInterface *p = x.clone();
    p->mul(y);
    return p;
}

anarion::ArrayInterface *
anarion::ArrayOperator::div(const anarion::ArrayInterface &x, const anarion::ArrayInterface &y) {
    ArrayInterface *p = x.clone();
    p->div(y);
    return p;
}

anarion::ArrayInterface * anarion::ArrayOperator::centralize(anarion::ArrayInterface &array) {
    ArrayInterface *ret = array.toFloat();
    float64 meanVal = mean(array);
    ret->sub(meanVal);
    return ret;
}

anarion::ArrayInterface * anarion::ArrayOperator::standardize(anarion::ArrayInterface &array) {
    ArrayInterface *ret = centralize(array);
    ret->div(stdVariance(*ret));
    return ret;
}

anarion::ArrayInterface *anarion::ArrayOperator::concat(const anarion::Vector<anarion::ArrayInterface *> &arrays) {
    size_type totalLength = 0;
    bool isInteger = true;
    for (size_type index = 0; index < arrays.size(); ++index) {
        totalLength += arrays[index]->length();
        isInteger = isInteger && arrays[index]->isInteger();
    }
    ArrayInterface *newArray;
    if (isInteger) {
        newArray = new BigIntegerArray(totalLength);
    } else {
        newArray = new BigFloatArray(totalLength);
    }
    for (size_type index = 0; index < arrays.size(); ++index) {
        ArrayInterface *array = arrays[index];
        for (size_type aindex = 0; aindex < array->length(); ++aindex) {
            if (isInteger) {
                newArray->push_back(array->getInteger(aindex));
            } else {
                newArray->push_back(array->getFloat(aindex));
            }
        }
    }
    return newArray;
}
