#pragma once
#include "base.hpp"

namespace math
{

template <typename T, int NumDims>
struct Array<T, false, NumDims>
{
    private:
        int size_;
        Array<T, false, NumDims-1>* data_;

    public:
        Array<T, false, NumDims>() {}

        template <typename ... OtherDims>
        Array<T, false, NumDims>(int _size, OtherDims... others)
        : size_(_size), data_(new Array<T, false, NumDims-1>[size_]) 
        {
            for(int index = 0; index < size_; ++index)
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

        int size() const
        {
            return size_;
        }
};

template <typename T>
struct Array<T, false, 1>
{
    private:
        int size_;
        T* data_;

    public:
        Array<T, false, 1>() {}

        Array<T, false, 1>(int _size)
        : size_(_size), data_(new T[size_]) {}

        T operator()(int index) const
        {
            return data_[index];
        }

        T& operator()(int index)
        {
            return data_[index];
        }

        int size() const
        {
            return size_;
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
    
} // namespace math::dynamic
