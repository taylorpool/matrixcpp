#pragma once

#include "static.hpp"
#include "dynamic.hpp"
#include "operators.hpp"

namespace math
{

template <typename T>
DynamicVector<T> operator*(T value, const DynamicVector<T>& vector)
{
    DynamicVector<T> answer = math::empty_like(vector);
    for(int index = 0; index < vector.length(); ++index)
    {
        answer(index) = value*vector(index);
    }
    return answer;
}

template <typename T, int Size>
StaticVector<T, Size> operator*(T value, const StaticVector<T, Size>& vector)
{
    StaticVector<T, Size> answer;
    for(int index = 0; index < Size; ++index)
    {
        answer(index) = value*vector(index);
    }
    return answer;
}

template <typename T, bool IsStatic, int FirstDim, int ... OtherDims>
requires(sizeof...(OtherDims) > 0 || FirstDim > 1)
Array<T, IsStatic, FirstDim, OtherDims...> operator*(T value, const Array<T, IsStatic, FirstDim, OtherDims...>& array)
{
    auto answer = math::empty_like(array);
    for(int index = 0; index < array.length(); ++index)
    {
        answer(index) = value*array(index);
    }
    return answer;
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape...> operator*(Array<T, IsStatic, Shape...> matrix, T value)
{
    return value*matrix;
}

template <typename T>
T dot(const DynamicVector<T>& left, const DynamicVector<T>& right)
{
    if(left.length() != right.length())
    {
        throw MismatchedLength(left.length(), right.length());
    }
    T dot_product = static_cast<T>(0);
    for(int index = 0; index < left.length(); ++index)
    {
        dot_product += left(index)*right(index);
    }
    return dot_product;
}

template <typename T, int M>
T dot(const StaticVector<T, M>& left, const StaticVector<T, M>& right)
{
    T dot_product = static_cast<T>(0);
    for(int index = 0; index < M; ++index)
    {
        dot_product += left(index)*right(index);
    }
    return dot_product;
}

template <typename T>
StaticVector<T, 3> cross(const StaticVector<T, 3>& left, const StaticVector<T, 3>& right)
{
    StaticVector<T, 3> result;
    result(0) = left(1)*right(2)-left(2)*right(1);
    result(1) = left(2)*right(0)-left(0)*right(2);
    result(2) = left(0)*right(1)-left(1)*right(0);
    return result;
}

template <typename T>
DynamicVector<T> cross(const DynamicVector<T>& left, const DynamicVector<T>& right)
{
    if(left.length() != 3)
    {
        throw MismatchedLength(left.length(), 3);
    }
    else if(right.length() != 3)
    {
        throw MismatchedLength(right.length(), 3);
    }
    DynamicVector<T> result = empty_like(left);
    result(0) = left(1)*right(2)-left(2)*right(1);
    result(1) = left(2)*right(0)-left(0)*right(2);
    result(2) = left(0)*right(1)-left(1)*right(0);
    return result;
}

template <typename T, int M>
StaticArray<T, M, M> outer(const StaticVector<T, M>& left, const StaticVector<T, M>& right)
{
    StaticArray<T, M, M> result;
    for(int row = 0; row < M; ++row)
    {
        for(int column = 0; column < M; ++column)
        {
            result(row,column) = left(row)*right(column);
        }
    }
    return result;
}

template <typename T>
DynamicMatrix<T> outer(const DynamicVector<T>& left, const DynamicVector<T>& right)
{
    int M = left.length();
    DynamicMatrix<T> result(M, M);
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
StaticVector<T, M> operator*(const StaticArray<T, M, N>& A, const StaticVector<T, N>& x)
{
    StaticVector<T, M> answer;
    for(int index = 0; index < M; ++index)
    {
        answer(index) = dot(A(index), x);
    }
    return answer;
}

template <typename T>
DynamicVector<T> operator*(const DynamicMatrix<T>& A, const DynamicVector<T>& x)
{
    DynamicVector<T> answer(A.length());
    for(int index = 0; index < answer.length(); ++index)
    {
        answer(index) = dot(A(index), x);
    }
    return answer;
}

template <typename T>
DynamicMatrix<T> operator*(const DynamicMatrix<T>& left, const DynamicMatrix<T>& right)
{
    int m = left.length();
    int n = right.length();
    if(left(0).length() != n)
    {
        throw MismatchedLength(left(0).length(), n);
    }
    int p = right(0).length();
    DynamicMatrix<T> result(m,p);
    for(int row = 0; row < m; ++row)
    {
        for(int column = 0; column < p; ++column)
        {
            result(row,column) = static_cast<T>(0);
            for(int index = 0; index < n; ++index)
            {
                result(row,column) += left(row,index)*right(index,column);
            }
        }
    }
    return result;
}

template <typename T, int M, int N, int P>
Array<T, true, M, P> operator*(const Array<T, true, M, N>& left, const Array<T, true, N, P>& right)
{
    auto answer = Array<T, true, M, P>(static_cast<T>(0));
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