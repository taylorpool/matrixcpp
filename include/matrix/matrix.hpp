#pragma once
#include <vector>

namespace math
{
template<typename T> 
class Matrix
{
    protected:
        std::vector<T> data_;

    public:
        Matrix(const std::vector<T>& input_data):
        data_(input_data)
        {
            
        };

        T operator[](int index) const
        {
            return data_[index];
        }

        T& operator[](int index)
        {
            return data_[index];
        }
};

using Matrixd = Matrix<double>;
}