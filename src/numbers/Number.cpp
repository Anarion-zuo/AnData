//
// Created by 左钰 on 2020/5/30.
//

#include "numbers/Number.h"

bool anarion::Integer::isInteger() const {
    return true;
}

bool anarion::Integer::isFloat() const {
    return false;
}

bool anarion::Float::isInteger() const {
    return false;
}

bool anarion::Float::isFloat() const {
    return true;
}
