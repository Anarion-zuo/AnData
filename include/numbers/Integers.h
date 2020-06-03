//
// Created by 左钰 on 2020/5/30.
//

#ifndef ANDATA_INTEGERS_H
#define ANDATA_INTEGERS_H


#include "Number.h"

namespace anarion {
    class Integer32 : public Integer {
    protected:
        int32 num;
    public:
        explicit Integer32(int32 num = 0) : num(num) {}

        uint64 getInteger() const override;
        float64 getFloat() const override;


        // operations
        Integer32 operator+(const Number &rhs) const { return Integer32(num + rhs.getInteger()); }
        Integer32 operator-(const Number &rhs) const { return Integer32(num - rhs.getInteger()); }
        Integer32 operator*(const Number &rhs) const { return Integer32(num * rhs.getInteger()); }
        Integer32 operator/(const Number &rhs) const { return Integer32(num / rhs.getInteger()); }
        Integer32 &operator+=(const Number &rhs) {
            num += rhs.getInteger();
            return *this;
        }
        Integer32 &operator-=(const Number &rhs) {
            num -= rhs.getInteger();
            return *this;
        }
        Integer32 &operator*=(const Number &rhs) {
            num *= rhs.getInteger();
            return *this;
        }
        Integer32 &operator/=(const Number &rhs) {
            num /= rhs.getInteger();
            return *this;
        }
        Integer32 operator-() const {
            return Integer32(-num);
        }
    };

    class Integer64 : public Integer {
    protected:
        int64 num;
    public:
        uint64 getInteger() const override;
        float64 getFloat() const override;
    };
}


#endif //ANDATA_INTEGERS_H
