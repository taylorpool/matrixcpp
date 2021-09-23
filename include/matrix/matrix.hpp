#pragma once
#include <array>
#include <numeric>

namespace math
{
template <typename T, int ... Shape>
class Matrix
{
    private:
        int num_dims_{static_cast<int>(sizeof...(Shape))};
        std::array<int, sizeof...(Shape)> shape_{{Shape...}};
        T data_[10];

    public:

        constexpr Matrix()
        {};

        constexpr Matrix Zeros()
        {
            auto matrix = Matrix();
            return matrix;
        }

        T operator()()
        {
            return data_[0];
        }

        template <typename First, typename ... OtherIndices>
        decltype(auto) operator()(First first, OtherIndices ... other_indices) 
        {
            return operator()(other_indices...);
        }

        std::array<int, sizeof...(Shape)> getShape() const
        {
            return shape_;
        }
};

template <typename T, int Size>
using Vector = Matrix<T, Size, 1>;

template <int ... Shape>
using Matrixd = Matrix<double, Shape ... >;
}