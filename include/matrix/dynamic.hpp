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
        Array(int _size)
        : size_(_size), data_(new Array<T, NumDims-1>[size_]) {}

        auto operator()(int index) const
        {
            return data_[index];
        }

        auto& operator()(int index)
        {
            return data_[index];
        }
};

template <typename T>
struct Array<T, 1>
{
    private:
        int size_;
        T* data_;

    public:
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
using Vectord = Vector<double>;

    
} // namespace math::dynamic
