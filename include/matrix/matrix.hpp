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
        std::vector<int> shape_;
        std::vector<T> data_;

    public:
        Matrix(const std::vector<T>& input_data):
        shape_({static_cast<int>(input_data.size())}),
        data_(input_data)
        {};

        Matrix(const std::vector<T>& input_data, const std::vector<int>& shape):
        shape_(shape),
        data_(input_data)
        {};
        Matrix<T> operator*(const Matrix<T>& x)
        {
            auto result_data = std::vector<T>();
            for(int i = 0; i < shape_[0]; ++i)
            {
                T sum = 0;
                for(int j = 0; j < x.getShape()[0]; ++j)
                {
                    sum = sum + data_[i*x.getShape()[0]+j]*x[j];
                }
                result_data.push_back(sum);
            } 
            auto result = Matrix<T>(result_data, {shape_[0]});
            return result;
        }

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
                shape_.cbegin(), 
                shape_.cend(), 
                1,
                std::multiplies<int>());
        }

        std::vector<int> getShape() const
        {
            return shape_;
        }
};

using Matrixd = Matrix<double>;
}