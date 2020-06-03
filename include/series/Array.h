//
// Created by 左钰 on 2020/5/30.
//

#ifndef ANDATA_ARRAY_H
#define ANDATA_ARRAY_H

#include <limits>
#include <container/List/Vector.hpp>
#include <base/container/SString.h>

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
//
//    template<typename num_type>
//    struct num_trait {
//        constexpr const static num_type max = num_type::max;
//        constexpr const static num_type min = num_type::min;
//        constexpr const static num_type zero = num_type::zero;
//
//        constexpr const static bool has_infinity = num_type::has_infinity;
//        constexpr const static num_type infinity = num_type::infinity;
//
//        constexpr const static bool has_nan = num_type::has_nan;
//        constexpr const static num_type nan = num_type::nan;
//
//        constexpr const static num_type epsilon = num_type::epsilon;
//
//    };

#define num_trait_vartype(num_type) \
    using pointer_type = num_type*;\
    using reference_type = num_type&;

#define num_trait_basic_type(num_type) \
    constexpr const static num_type max = std::numeric_limits<num_type>::max();\
    constexpr const static num_type min = std::numeric_limits<num_type>::min();\
    constexpr const static num_type zero = 0;\
\
    constexpr const static bool has_infinity = std::numeric_limits<num_type>::has_infinity;\
    constexpr const static num_type infinity = std::numeric_limits<num_type>::infinity();\
\
    constexpr const static bool has_nan = std::numeric_limits<num_type>::has_quiet_NaN;\
    constexpr const static num_type nan = std::numeric_limits<num_type>::quiet_NaN();\
\
    constexpr const static num_type epsilon = std::numeric_limits<num_type>::epsilon();\

//
//    template<>
//    struct num_trait<int8> {
//        num_trait_vartype(int8)
//
//        num_trait_basic_type(int8)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<int16> {
//        num_trait_vartype(int16)
//
//        num_trait_basic_type(int16)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<int32> {
//        num_trait_vartype(int32)
//
//        num_trait_basic_type(int32)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<int64> {
//        num_trait_vartype(int64)
//
//        num_trait_basic_type(int64)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<uint8> {
//        num_trait_vartype(uint8)
//
//        num_trait_basic_type(uint8)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = true;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<uint16> {
//        num_trait_vartype(uint16)
//
//        num_trait_basic_type(uint16)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = true;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<uint32> {
//        num_trait_vartype(uint32)
//
//        num_trait_basic_type(uint32)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = true;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<uint64> {
//        num_trait_vartype(uint64)
//
//        num_trait_basic_type(uint64)
//
//        constexpr const static bool is_integer = true;
//        constexpr const static bool is_precise = true;
//        constexpr const static bool is_unsigned = true;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<float32> {
//        num_trait_vartype(float32)
//        num_trait_basic_type(float32)
//        constexpr const static bool is_integer = false;
//        constexpr const static bool is_precise = false;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };
//
//    template<>
//    struct num_trait<float64> {
//        num_trait_vartype(float64)
//        num_trait_basic_type(float64)
//        constexpr const static bool is_integer = false;
//        constexpr const static bool is_precise = false;
//        constexpr const static bool is_unsigned = false;
//        constexpr const static bool is_bounded = true;
//    };

    struct ArrayException : public std::exception {};
    struct ArraySizeNotMatch : public ArrayException {};

    template <typename num_type>
    class Array : public Vector<num_type> {
        using this_type = Array<num_type>;
        using parent_type = Vector<num_type>;
    public:
        Array() = default;
        ~Array() override = default;
        Array(const this_type &) = default;
        Array(this_type &&) noexcept = default;
        Array &operator=(const this_type &) = default;
        Array &operator=(this_type &&) noexcept = default;

        explicit Array(size_type initSize) : parent_type(initSize) {}
        Array(std::initializer_list<num_type> &&initList)
            : parent_type(forward<std::initializer_list<num_type>>(initList)) {}
        Array(size_type initSize, const num_type &num) : parent_type(initSize, num) {}

        void concat(const this_type &rhs) {
            this->insert(this->cur, rhs.begin, rhs.cur);
        }

        // arithmetic operations
#pragma region operators
#define operator_seq(c) \
    if (rhs.size() != this->size()) {\
        throw ArraySizeNotMatch();\
    }\
    if (this->empty()) {\
        return this_type();\
    }\
    this_type ret(this->size());\
    for (size_type index = 0; index < this->size(); ++index) {\
        ret.push_back((*this)[index] c rhs[index]);\
    }\
    return move(ret);
        this_type operator+(const this_type &rhs) const {
            operator_seq(+)
        }
        this_type operator-(const this_type &rhs) const {
            operator_seq(-)
        }
        this_type operator*(const this_type &rhs) const {
            operator_seq(*)
        }
        this_type operator/(const this_type &rhs) const {
            operator_seq(/)
        }

#define operator_static(cc) \
        if (rhs.size() != this->size()) {\
            throw ArraySizeNotMatch();\
        }\
        if (this->empty()) {\
            return *this;\
        }\
        for (size_type index = 0; index < this->size(); ++index) {\
            (*this)[index] cc rhs[index];\
        }\
        return *this;

        this_type &operator+=(const this_type &rhs) {
            operator_static(+=)
        }
        this_type &operator-=(const this_type &rhs) {
            operator_static(-=)
        }
        this_type &operator*=(const this_type &rhs) {
            operator_static(*=)
        }
        this_type &operator/=(const this_type &rhs) {
            operator_static(/=)
        }
#pragma endregion
#pragma region arithmetic
        num_type sum(size_type beginIndex, size_type endIndex) {
            if (beginIndex >= this->size()) {
                throw IndexOutOfRange();
            }
            if (endIndex > this->size()) {
                throw IndexOutOfRange();
            }
            num_type ret = type_trait<num_type>::zero;
            for (auto it = this->begin_iterator() + beginIndex; index != this->end_iterator(); ++it) {
                ret += *it;
            }
            return move(ret);
        }
        num_type sum() { return sum(0, this->size()); }
        num_type mean(size_type beginIndex, size_type endIndex) {
            if (beginIndex >= this->size()) {
                throw IndexOutOfRange();
            }
            if (endIndex > this->size()) {
                throw IndexOutOfRange();
            }
            num_type ret = type_trait<num_type>::zero;
            size_type count = 0;
            for (auto it = this->begin_iterator() + beginIndex; index != this->end_iterator(); ++it, ++count) {
                ret = (ret * count + *it) / (count + 1);
            }
        }
        num_type mean() { return mean(0, this->size()); }
#pragma endregion

    };

    class ArrayInterface {
    public:
        virtual ~ArrayInterface() = default;

        virtual bool isInteger() const = 0;
        virtual ArrayInterface *clone() const = 0;

        virtual size_type length() const = 0;

        // reference
        virtual int64 getInteger(size_type index) const = 0;
        virtual float64 getFloat(size_type index) const = 0;
        virtual void setInteger(anarion::size_type index, uint64 num) = 0;
        virtual void setFloat(size_type index, float64 num) = 0;

        // arithmetic
        void add(const ArrayInterface &rhs);
        void sub(const ArrayInterface &rhs);
        void mul(const ArrayInterface &rhs);
        void div(const ArrayInterface &rhs);
        void add(float64 rhs);
        void sub(float64 rhs);
        void mul(float64 rhs);
        void div(float64 rhs);

        // transform
        ArrayInterface *toFloat() const ;
        ArrayInterface *toInteger() const ;

        // structural
        virtual void resize(size_type newSize) = 0;
        virtual void push_back(float64 number) = 0;
        virtual void push_back(int64 number) = 0;
        virtual void insert(size_type index, float64 number) = 0;
        virtual void insert(size_type index, int64 number) = 0;
        virtual void remove(size_type index) = 0;

    };

    class IntegerArray : public Array<int32>, public ArrayInterface {
    public:
        IntegerArray() = default;
        ~IntegerArray() override = default;
        explicit IntegerArray(size_type initSize) : Array<int32>(initSize) {}
        IntegerArray(size_type initSize, int32 number) : Array<int32>(initSize, number) {}

        bool isInteger() const override;

        int64 getInteger(size_type index) const override;
        float64 getFloat(size_type index) const override;

        void setInteger(anarion::size_type index, uint64 num) override;
        void setFloat(size_type index, float64 num) override;

        ArrayInterface *clone() const override;

        size_type length() const override {
            return size();
        }

        void resize(size_type newSize) override;
        void push_back(float64 number) override;
        void push_back(int64 number) override;
        void insert(size_type index, float64 number) override;
        void insert(size_type index, int64 number) override;
        void remove(size_type index) override;

    };

    class BigIntegerArray : public Array<int64>, public ArrayInterface {
    public:
        BigIntegerArray() = default;
        ~BigIntegerArray() override = default;
        explicit BigIntegerArray(size_type initSize) : Array<int64>(initSize) {}
        BigIntegerArray(size_type initSize, int32 number) : Array<int64>(initSize, number) {}

        int64 getInteger(size_type index) const override;
        float64 getFloat(size_type index) const override;

        bool isInteger() const override;

        void setInteger(anarion::size_type index, uint64 num) override;
        void setFloat(size_type index, float64 num) override;

        ArrayInterface *clone() const override;
        size_type length() const override {
            return size();
        }

        void resize(size_type newSize) override;
        void push_back(float64 number) override;
        void push_back(int64 number) override;
        void insert(size_type index, float64 number) override;
        void insert(size_type index, int64 number) override;
        void remove(size_type index) override;

    };

    class FloatArray : public Array<float32>, public ArrayInterface {
    public:
        FloatArray() = default;
        ~FloatArray() override = default;
        explicit FloatArray(size_type initSize) : Array<float32>(initSize) {}
        FloatArray(size_type initSize, int32 number) : Array<float32>(initSize, number) {}

        bool isInteger() const override;

        int64 getInteger(size_type index) const override;
        float64 getFloat(size_type index) const override;

        void setInteger(anarion::size_type index, uint64 num) override;
        void setFloat(size_type index, float64 num) override;

        ArrayInterface *clone() const override;
        size_type length() const override {
            return size();
        }

        void resize(size_type newSize) override;
        void push_back(float64 number) override;
        void push_back(int64 number) override;
        void insert(size_type index, float64 number) override;
        void insert(size_type index, int64 number) override;
        void remove(size_type index) override;

    };

    class BigFloatArray : public Array<float64>, public ArrayInterface {
    public:
        BigFloatArray() = default;
        ~BigFloatArray() override = default;
        explicit BigFloatArray(size_type initSize) : Array<float64>(initSize) {}
        BigFloatArray(size_type initSize, int32 number) : Array<float64>(initSize, number) {}

        bool isInteger() const override;

        int64 getInteger(size_type index) const override;
        float64 getFloat(size_type index) const override;

        void setInteger(anarion::size_type index, uint64 num) override;
        void setFloat(size_type index, float64 num) override;

        ArrayInterface *clone() const override;
        size_type length() const override {
            return size();
        }

        void resize(size_type newSize) override;
        void push_back(float64 number) override;
        void push_back(int64 number) override;
        void insert(size_type index, float64 number) override;
        void insert(size_type index, int64 number) override;
        void remove(size_type index) override;

    };

    class StringArray : public Vector<SString>, public ArrayInterface {
    public:
        StringArray() = default;
        ~StringArray() override = default;
        explicit StringArray(size_type initSize) : Vector<SString>(initSize) {}

        bool isInteger() const override;

        void setInteger(anarion::size_type index, uint64 num) override;
        void setFloat(size_type index, float64 num) override;

        ArrayInterface *clone() const override;

        int64 getInteger(size_type index) const override;
        float64 getFloat(size_type index) const override;
        size_type length() const override {
            return size();
        }
    };
}



#endif //ANDATA_ARRAY_H
