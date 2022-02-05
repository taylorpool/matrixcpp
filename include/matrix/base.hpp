#pragma once

#include <exception>

namespace math
{
template <typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template <typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

template <typename T, bool IsStatic, int ... Dims> class Array;

template <bool IsStatic, int ... Shape>
using Arrayi = Array<int, IsStatic, Shape ... >;

template <bool IsStatic, int ... Shape>
using Arrayf = Array<float, IsStatic, Shape ... >;

template <bool IsStatic, int ... Shape>
using Arrayd = Array<double, IsStatic, Shape ... >;

class OutOfRange: public std::exception
{
    private:
        int index_;
        int size_;

    public:
        OutOfRange(int index, int size)
        : index_(index), size_(size) {};

        ~OutOfRange() override {};

        const char* what() const noexcept override 
        {
            return "index invalid for size";
        }
};
}