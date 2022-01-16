#pragma once

namespace math::dynamic
{

template <typename T, int NumDims>
struct Array
{
    private:
        int size_;
        Array<T, NumDims-1>* data_;

    public:
        Array() {}

        template <typename ... OtherDims>
        Array(int _size, OtherDims... others)
        : size_(_size), data_(new Array<T, NumDims-1>[size_]) 
        {
            for(int index = 0; index < size_; ++index)
            {
                data_[index] = Array<T, NumDims-1>(others...);
            }
        }

        Array<T, NumDims-1> operator()(int index) const
        {
            return data_[index];
        }

        Array<T, NumDims-1>& operator()(int index)
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
struct Array<T, 1>
{
    private:
        int size_;
        T* data_;

    public:
        Array() {}

        Array(int _size)
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

template <typename T>
using Vector = Array<T, 1>;

using Vectori = Vector<int>;
using Vectorf = Vector<float>;
using Vectord = Vector<double>;

template <int NumDims>
using Arrayi = Array<int, NumDims>;

template <int NumDims>
using Arrayf = Array<int, NumDims>;

template <int NumDims>
using Arrayd = Array<double, NumDims>;
    
} // namespace math::dynamic
