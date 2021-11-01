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

template <typename T, int ... Dims> class Matrix;

template <typename T, int Dim>
class Matrix<T, Dim>
{
    private:
        T data_[Dim];

    public:
        Matrix(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < Dim; ++i)
            {
                data_[i] = initial_value;
            }
        }

        T operator()(int index) const
        {
            return data_[index];
        }
};

template <typename T, int FirstDim, int ... OtherDim>
class Matrix<T, FirstDim, OtherDim...>
{
    private:
        Matrix<T, OtherDim...> data_[FirstDim];

    public:
        Matrix(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < FirstDim; ++i)
            {
                data_[i] = Matrix<T, OtherDim...>(initial_value);
            }
        }

        Matrix<T, OtherDim...> operator()(int index) const
        {
            return data_[index];
        }
};

template <typename T, int Size>
using Vector = Matrix<T, Size>;

template <int ... Shape>
using Matrixd = Matrix<double, Shape ... >;

template <typename T, int FirstDim, int ... Shape>
bool operator==(const Matrix<T, FirstDim, Shape...>& left, const Matrix<T, FirstDim, Shape...>& right)
{
    for(int index = 0; index < FirstDim; ++index)
    {
        if(left(index) != right(index))
        {
            return false;
        }
    }
    return true;
}

template <typename T, int FirstDim, int ... Shape>
bool operator!=(const Matrix<T, FirstDim, Shape...>& left, const Matrix<T, FirstDim, Shape...>& right)
{
    return false == (left == right);
}

// template<typename T, int M, int N>
// Vector<T, M> operator*(const Matrix<T, M, N>& A, const Vector<T, N>& x)
// {
//     return Vector<T, M>(static_cast<T>(0));
// }

}