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

        T& operator()(int index)
        {
            return data_[index];
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

        Matrix<T, OtherDim...>& operator()(int index)
        {
            return data_[index];
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

template <typename T, int M>
T dot(const Vector<T, M>& left, const Vector<T, M>& right)
{
    T dot_product = static_cast<T>(0);
    for(int index = 0; index < M; ++index)
    {
        dot_product += left(index)*right(index);
    }
    return dot_product;
}

template<typename T, int M, int N>
Vector<T, M> operator*(const Matrix<T, M, N>& A, const Vector<T, N>& x)
{
    auto answer = Vector<T, M>();
    for(int index = 0; index < M; ++index)
    {
        answer(index) = dot(A(index), x);
    }
    return answer;
}

template <typename T, int M, int N, int P>
Matrix<T, M, P> operator*(const Matrix<T, M, N>& left, const Matrix<T, N, P>& right)
{
    auto answer = Matrix<T, M, P>();
    for(int row = 0; row < M; ++row)
    {
        for(int column = 0; column < P; ++ column)
        {
            T sum = static_cast<T>(0);
            for(int index = 0; index < N; ++index)
            {
                sum += left(row)(index)*right(index)(column);
            }
            answer(row)(column) = sum;
        }
    }
    return answer;
}

}