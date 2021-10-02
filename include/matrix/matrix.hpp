#pragma once

namespace math
{

constexpr int product()
{
    return 1;
}

template <typename First, typename ... Other>
constexpr int product(First first, Other ... others)
{
    return first * product(others...);
}

template <typename T, int ... Shape>
class Matrix
{
    private:
        int num_dims_{static_cast<int>(sizeof...(Shape))};
        int size_ = product(Shape...); 
        T data_[product(Shape...)];

        Matrix();

    public:
        Matrix(T initial_value)
        {
            for(int i = 0; i < size_; ++i)
            {
                data_[i] = initial_value;
            }
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

        int getDimension() const
        {
            return num_dims_;
        }

        int getSize() const
        {
            return size_;
        }
};

template <typename T, int Size>
using Vector = Matrix<T, Size>;

template <int ... Shape>
using Matrixd = Matrix<double, Shape ... >;
}