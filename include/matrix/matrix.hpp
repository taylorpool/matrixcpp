#pragma once
#include <vector>
#include <numeric>
#include <functional>

namespace math
{
template<typename T> 
class Matrix
{
    protected:
        std::vector<int> dimensions_;
        std::vector<T> data_;

    public:
        Matrix(const std::vector<T>& input_data):
        dimensions_({static_cast<int>(input_data.size())}),
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

        int getSize() const
        {
            return std::accumulate(
                dimensions_.cbegin(), 
                dimensions_.cend(), 
                1,
                std::multiplies<int>());
        }

        std::vector<int> getShape() const
        {
            return dimensions_;
        }
};

using Matrixd = Matrix<double>;
}