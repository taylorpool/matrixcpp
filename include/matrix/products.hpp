#pragma once

#include "base.hpp"

namespace math
{

template <typename T, int Size>
Vector<T, Size> operator*(T value, Vector<T, Size> vector)
{
    decltype(vector) answer;
    for(int index = 0; index < Size; ++index)
    {
        answer(index) = value*vector(index);
    }
    return answer;
}

template <typename T, int FirstDim, int SecondDim, int ... OtherDims>
Matrix<T, FirstDim, SecondDim, OtherDims...> operator*(T value, Matrix<T, FirstDim, SecondDim, OtherDims...> matrix)
{
    decltype(matrix) answer;
    for(int index = 0; index < FirstDim; ++index)
    {
        answer(index) = value*matrix(index);
    }
    return answer;
}

template <typename T, int ... Shape>
Matrix<T, Shape...> operator*(Matrix<T, Shape...> matrix, T value)
{
    return value*matrix;
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
    auto answer = Matrix<T, M, P>(static_cast<T>(0));
    for(int row = 0; row < M; ++row)
    {
        for(int column = 0; column < P; ++ column)
        {
            for(int index = 0; index < N; ++index)
            {
                answer(row,column) += left(row,index)*right(index,column);
            }
        }
    }
    return answer;
}
}