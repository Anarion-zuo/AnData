//
// Created by 左钰 on 2020/5/30.
//

#include "series/Array.h"

bool anarion::IntegerArray::isInteger() const {
    return true;
}

anarion::int64 anarion::IntegerArray::getInteger(anarion::size_type index) const {
    return get(index);
}

anarion::float64 anarion::IntegerArray::getFloat(anarion::size_type index) const {
    return get(index);
}

anarion::ArrayInterface *anarion::IntegerArray::clone() const {
    return new IntegerArray(*this);
}

void anarion::IntegerArray::setInteger(anarion::size_type index, uint64 num) {
    get(index) = num;
}

void anarion::IntegerArray::setFloat(size_type index, float64 num) {
    get(index) = num;
}

void anarion::IntegerArray::resize(anarion::size_type newSize) {
    Vector<int32>::resize(newSize);
}

void anarion::IntegerArray::push_back(anarion::float64 number) {
    Vector<int32>::push_back(number);
}

void anarion::IntegerArray::push_back(anarion::int64 number) {
    Vector<int32>::push_back(number);
}

void anarion::IntegerArray::insert(anarion::size_type index, anarion::float64 number) {
    Vector<int32>::insert(index, number);
}

void anarion::IntegerArray::insert(anarion::size_type index, anarion::int64 number) {
    Vector<int32>::insert(index, number);
}

void anarion::IntegerArray::remove(anarion::size_type index) {
    Vector<int32>::remove(index);
}

bool anarion::FloatArray::isInteger() const {
    return false;
}

anarion::int64 anarion::FloatArray::getInteger(anarion::size_type index) const {
    return get(index);
}

anarion::float64 anarion::FloatArray::getFloat(anarion::size_type index) const {
    return get(index);
}

anarion::ArrayInterface *anarion::FloatArray::clone() const {
    return new FloatArray(*this);
}

void anarion::FloatArray::setInteger(anarion::size_type index, anarion::uint64 num) {
    get(index) = num;
}

void anarion::FloatArray::setFloat(anarion::size_type index, anarion::float64 num) {
    get(index) = num;
}


void anarion::FloatArray::resize(anarion::size_type newSize) {
    Vector<float32>::resize(newSize);
}

void anarion::FloatArray::push_back(anarion::float64 number) {
    Vector<float32>::push_back(number);
}

void anarion::FloatArray::push_back(anarion::int64 number) {
    Vector<float32>::push_back(number);
}

void anarion::FloatArray::insert(anarion::size_type index, anarion::float64 number) {
    Vector<float32>::insert(index, number);
}

void anarion::FloatArray::insert(anarion::size_type index, anarion::int64 number) {
    Vector<float32>::insert(index, number);
}

void anarion::FloatArray::remove(anarion::size_type index) {
    Vector<float32>::remove(index);
}


bool anarion::BigIntegerArray::isInteger() const {
    return true;
}

anarion::int64 anarion::BigIntegerArray::getInteger(anarion::size_type index) const {
    return get(index);
}

anarion::float64 anarion::BigIntegerArray::getFloat(anarion::size_type index) const {
    return get(index);
}

anarion::ArrayInterface *anarion::BigIntegerArray::clone() const {
    return new BigIntegerArray(*this);
}

void anarion::BigIntegerArray::setInteger(anarion::size_type index, anarion::uint64 num) {
    get(index) = num;
}

void anarion::BigIntegerArray::setFloat(anarion::size_type index, anarion::float64 num) {
    get(index) = num;
}

void anarion::BigIntegerArray::resize(anarion::size_type newSize) {
    Vector<int64>::resize(newSize);
}

void anarion::BigIntegerArray::push_back(anarion::float64 number) {
    Vector<int64>::push_back(number);
}

void anarion::BigIntegerArray::push_back(anarion::int64 number) {
    Vector<int64>::push_back(number);
}

void anarion::BigIntegerArray::insert(anarion::size_type index, anarion::float64 number) {
    Vector<int64>::insert(index, number);
}

void anarion::BigIntegerArray::insert(anarion::size_type index, anarion::int64 number) {
    Vector<int64>::insert(index, number);
}

void anarion::BigIntegerArray::remove(anarion::size_type index) {
    Vector<int64>::remove(index);
}

bool anarion::BigFloatArray::isInteger() const {
    return false;
}

anarion::int64 anarion::BigFloatArray::getInteger(anarion::size_type index) const {
    return get(index);
}

anarion::float64 anarion::BigFloatArray::getFloat(anarion::size_type index) const {
    return get(index);
}

anarion::ArrayInterface *anarion::BigFloatArray::clone() const {
    return new BigFloatArray(*this);
}

void anarion::BigFloatArray::setInteger(anarion::size_type index, anarion::uint64 num) {
    get(index) = num;
}

void anarion::BigFloatArray::setFloat(anarion::size_type index, anarion::float64 num) {
    get(index) = num;
}

void anarion::BigFloatArray::resize(anarion::size_type newSize) {
    Vector<float64>::resize(newSize);
}

void anarion::BigFloatArray::push_back(anarion::float64 number) {
    Vector<float64>::push_back(number);
}

void anarion::BigFloatArray::push_back(anarion::int64 number) {
    Vector<float64>::push_back(number);
}

void anarion::BigFloatArray::insert(anarion::size_type index, anarion::float64 number) {
    Vector<float64>::insert(index, number);
}

void anarion::BigFloatArray::insert(anarion::size_type index, anarion::int64 number) {
    Vector<float64>::insert(index, number);
}

void anarion::BigFloatArray::remove(anarion::size_type index) {
    Vector<float64>::remove(index);
}

bool anarion::StringArray::isInteger() const {
    return false;
}

anarion::int64 anarion::StringArray::getInteger(anarion::size_type index) const {
    return 0;
}

anarion::float64 anarion::StringArray::getFloat(anarion::size_type index) const {
    return 0;
}

void anarion::StringArray::setInteger(anarion::size_type index, anarion::uint64 num) {
//    get(index) = num;
}

void anarion::StringArray::setFloat(anarion::size_type index, anarion::float64 num) {
//    get(index) = num;
}

anarion::ArrayInterface *anarion::StringArray::clone() const {
    return nullptr;
}

void anarion::ArrayInterface::add(const anarion::ArrayInterface &rhs) {
    for (size_type index = 0; index < rhs.length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number + rhs.getInteger(index));
        } else {
            float64 number = getFloat(index);
            setFloat(index, number + rhs.getFloat(index));
        }
    }
}

void anarion::ArrayInterface::sub(const anarion::ArrayInterface &rhs) {
    for (size_type index = 0; index < rhs.length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number - rhs.getInteger(index));
        } else {
            float64 number = getFloat(index);
            setFloat(index, number - rhs.getFloat(index));
        }
    }
}

void anarion::ArrayInterface::mul(const anarion::ArrayInterface &rhs) {
    for (size_type index = 0; index < rhs.length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number * rhs.getInteger(index));
        } else {
            float64 number = getFloat(index);
            setFloat(index, number * rhs.getFloat(index));
        }
    }
}

void anarion::ArrayInterface::div(const anarion::ArrayInterface &rhs) {
    for (size_type index = 0; index < rhs.length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number / rhs.getInteger(index));
        } else {
            float64 number = getFloat(index);
            setFloat(index, number / rhs.getFloat(index));
        }
    }
}

anarion::ArrayInterface *anarion::ArrayInterface::toFloat() const {
    ArrayInterface *array = new FloatArray(length(), 0);
    for (size_type index = 0; index < length(); ++index) {
        array->setFloat(index, getFloat(index));
    }
    return array;
}

anarion::ArrayInterface *anarion::ArrayInterface::toInteger() const {
    ArrayInterface *array = new IntegerArray(length(), 0);
    for (size_type index = 0; index < length(); ++index) {
        array->setInteger(index, getInteger(index));
    }
    return array;
}

void anarion::ArrayInterface::add(anarion::float64 rhs) {
    for (size_type index = 0; index < length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number + rhs);
        } else {
            float64 number = getFloat(index);
            setFloat(index, number + rhs);
        }
    }
}

void anarion::ArrayInterface::sub(anarion::float64 rhs) {
    for (size_type index = 0; index < length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number - rhs);
        } else {
            float64 number = getFloat(index);
            setFloat(index, number - rhs);
        }
    }
}

void anarion::ArrayInterface::mul(anarion::float64 rhs) {
    for (size_type index = 0; index < length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number * rhs);
        } else {
            float64 number = getFloat(index);
            setFloat(index, number * rhs);
        }
    }
}

void anarion::ArrayInterface::div(anarion::float64 rhs) {
    for (size_type index = 0; index < length(); ++index) {
        if (isInteger()) {
            int64 number = getInteger(index);
            setInteger(index, number / rhs);
        } else {
            float64 number = getFloat(index);
            setFloat(index, number / rhs);
        }
    }
}

