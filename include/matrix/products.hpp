#pragma once

#include "static.hpp"
#include "operators.hpp"

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
Array<T, FirstDim, SecondDim, OtherDims...> operator*(T value, Array<T, FirstDim, SecondDim, OtherDims...> matrix)
{
    decltype(matrix) answer;
    for(int index = 0; index < FirstDim; ++index)
    {
        answer(index) = value*matrix(index);
    }
    return answer;
}

template <typename T, int ... Shape>
Array<T, Shape...> operator*(Array<T, Shape...> matrix, T value)
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

template <typename T>
Vector<T, 3> cross(const Vector<T, 3>& left, const Vector<T, 3>& right)
{
    Vector<T, 3> result;
    result(0) = left(1)*right(2)-left(2)*right(1);
    result(1) = left(2)*right(0)-left(0)*right(2);
    result(2) = left(0)*right(1)-left(1)*right(0);
    return result;
}

template <typename T, int M>
Array<T, M, M> outer(const Vector<T, M>& left, const Vector<T, M>& right)
{
    Array<T, M, M> result;
    for(int row = 0; row < M; ++row)
    {
        for(int column = 0; column < M; ++column)
        {
            result(row,column) = left(row)*right(column);
        }
    }
    return result;
}

template<typename T, int M, int N>
Vector<T, M> operator*(const Array<T, M, N>& A, const Vector<T, N>& x)
{
    auto answer = Vector<T, M>();
    for(int index = 0; index < M; ++index)
    {
        answer(index) = dot(A(index), x);
    }
    return answer;
}

template <typename T, int M, int N, int P>
Array<T, M, P> operator*(const Array<T, M, N>& left, const Array<T, N, P>& right)
{
    auto answer = Array<T, M, P>(static_cast<T>(0));
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