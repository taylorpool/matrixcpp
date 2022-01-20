#pragma once
#include "base.hpp"

namespace math
{

template <typename T, int NumDims>
requires(NumDims > 1)
struct Array<T, false, NumDims>
{
    private:
        int length_;
        Array<T, false, NumDims-1>* data_;

    public:
        Array<T, false, NumDims>() {}

        template <typename ... OtherDims>
        Array<T, false, NumDims>(int _length, OtherDims... others)
        : length_(_length), data_(new Array<T, false, NumDims-1>[length_]) 
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index] = Array<T, false, NumDims-1>(others...);
            }
        }

        Array<T, false, NumDims-1> operator()(int index) const
        {
            return data_[index];
        }

        Array<T, false, NumDims-1>& operator()(int index)
        {
            return data_[index];
        }

        template <typename ... OtherIndices>
        auto operator()(int index0, int index1, OtherIndices... others) const
        {
            return data_[index0](index1, others...);
        }

        template <typename ... OtherIndices>
        auto& operator()(int index0, int index1, OtherIndices... others)
        {
            return data_[index0](index1, others...);
        }

        int length() const
        {
            return length_;
        }
};

template <typename T>
struct Array<T, false, 1>
{
    private:
        int length_;
        T* data_;

    public:
        Array<T, false, 1>()
        : length_(0) {}

        Array<T, false, 1>(int _length)
        : length_(_length), data_(new T[length_]) {}

        void check_input(int index) const
        {
            if(index >= length_ || index < 0)
            {
                throw OutOfRange(index, length_);
            }
        }

        T operator()(int index) const
        {
            check_input(index);
            return data_[index];
        }

        T& operator()(int index)
        {
            check_input(index);
            return data_[index];
        }

        int length() const
        {
            return length_;
        }

        void fill(T value)
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index] = value;
            }
        }
};

template <typename T, int NumDims>
using DynamicArray = Array<T, false, NumDims>;

template <int NumDims>
using DynamicArrayi = DynamicArray<int, NumDims>;

template <int NumDims>
using DynamicArrayf = DynamicArray<float, NumDims>;

template <int NumDims>
using DynamicArrayd = DynamicArray<double, NumDims>;

template <typename T>
using DynamicVector = DynamicArray<T, 1>;

using DynamicVectori = DynamicVector<int>;

using DynamicVectorf = DynamicVector<float>;

using DynamicVectord = DynamicVector<double>;
    
} // namespace math
