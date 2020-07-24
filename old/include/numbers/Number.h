//
// Created by 左钰 on 2020/5/30.
//

#ifndef ANDATA_NUMBER_H
#define ANDATA_NUMBER_H

namespace anarion {
    using int8 = char;
    using int16 = short;
    using int32 = int;
    using int64 = long;
    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long;
    using float32 = float;
    using float64 = double;
    using float80 = long double;

    class Number {
    public:
        virtual ~Number() = default;

        virtual bool isInteger() const = 0;
        virtual bool isFloat() const = 0;
        virtual uint64 getInteger() const = 0;
        virtual float64 getFloat() const = 0;
    };

    class Integer : public Number {
    public:
        bool isInteger() const override;
        bool isFloat() const override;
    };

    class Float : public Number {
    public:
        bool isInteger() const override;
        bool isFloat() const override;
    };
}

#endif //ANDATA_NUMBER_H
