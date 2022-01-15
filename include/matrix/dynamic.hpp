#pragma once
#include <vector>

namespace math::dynamic
{

template <typename T, int NumDims>
struct Array
{
    private:
        std::vector<Array<T, NumDims-1>> data_;
        int size;

    public:
        auto operator()(int index) const
        {
            return data_[index];
        }

        auto& operator()(int index)
        {
            return &data_[index];
        }
};

template <typename T>
struct Array<T, 1>
{
    private:
        std::vector<T> data_;

    public:
        Array(int _size)
        :  data_(_size) {}

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
            return data_.size();
        }
};

template <typename T>
using Vector = Array<T, 1>;

using Vectori = Vector<int>;

    
} // namespace math::dynamic
