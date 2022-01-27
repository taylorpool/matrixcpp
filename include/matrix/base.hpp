#pragma once

#include <exception>

namespace math
{

template <typename T, bool IsStatic, int ... Dims> class Array;

template <bool IsStatic, int ... Shape>
using Arrayi = Array<int, IsStatic, Shape ... >;

template <bool IsStatic, int ... Shape>
using Arrayf = Array<float, IsStatic, Shape ... >;

template <bool IsStatic, int ... Shape>
using Arrayd = Array<double, IsStatic, Shape ... >;

template <typename T, bool IsStatic, int Size>
using Vector = Array<T, IsStatic, Size>;

template <bool IsStatic, int Size>
using Vectori = Vector<int, IsStatic, Size>;

template <bool IsStatic, int Size>
using Vectorf = Vector<float, IsStatic, Size>;

template <bool IsStatic, int Size>
using Vectord = Vector<double, IsStatic, Size>;

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