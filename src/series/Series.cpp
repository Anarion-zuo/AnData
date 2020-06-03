//
// Created by 左钰 on 2020/5/30.
//

#include <series/Array.h>
#include "series/Series.h"

anarion::Series::Series(anarion::NumType numType) : numType(numType) {
    switch (numType) {
        case Int8:
            array = new Array<int8>();
            break;
        case Int16:
            array = new Array<int16>();
            break;
        case Int32:
            array = new Array<int32>();
            break;
        case Int64:
            array = new Array<int64>();
            break;
        case Uint8:
            array = new Array<uint8>();
            break;
        case Uint16:
            array = new Array<uint16>();
            break;
        case Uint32:
            array = new Array<uint32>();
            break;
        case Uint64:
            array = new Array<uint64>();
            break;
        case Float32:
            array = new Array<float32>();
            break;
        case Float64:
            array = new Array<float64>();
            break;
        default:
            array = nullptr;
            break;
    }
}
