//
// Created by 左钰 on 2020/5/30.
//

#ifndef ANDATA_SERIES_H
#define ANDATA_SERIES_H

namespace anarion {
    enum NumType {
        Int8, Int16, Int32, Int64,
        Uint8, Uint16, Uint32, Uint64,
        Float32, Float64,
        StringObject,
    };
    class Series {
    protected:
        enum NumType numType;
        void *array;  // pointer to array
    public:
        explicit Series(enum NumType numType = Float32);
    };
}

#endif //ANDATA_SERIES_H
