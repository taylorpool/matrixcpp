#pragma once

#include "static.hpp"
#include "dynamic.hpp"

namespace math
{

template <typename T>
DynamicMatrix<T> triu(const DynamicMatrix<T>& matrix)
{
    int N = matrix.length();
    DynamicMatrix<T> upper_triangular(N,N);
    auto zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column < row; ++column)
        {
            upper_triangular(row,column) = zero_element;
        }
        for(int column = row; column < N; ++column)
        {
            upper_triangular(row,column) = matrix(row,column);
        }
    }
    return upper_triangular;
}

template <typename T, int N>
Array<T, true, N, N> triu(const Array<T, true, N, N>& matrix)
{
    Array<T, true, N, N> upper_triangular;
    auto zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column < row; ++column)
        {
            upper_triangular(row, column) = zero_element;
        }
        for(int column = row; column < N; ++column)
        {
            upper_triangular(row, column) = matrix(row, column);
        }
    }
    return upper_triangular;
}

template <typename T>
DynamicMatrix<T> tril(const DynamicMatrix<T>& matrix)
{
    int N = matrix.length();
    DynamicMatrix<T> lower_triangular(N,N);
    auto zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column <= row; ++column)
        {
            lower_triangular(row,column) = matrix(row,column);
        }
        for(int column = row+1; column < N; ++column)
        {
            lower_triangular(row,column) = zero_element;
        }
    }
    return lower_triangular;
}

template <typename T, int N>
Array<T, true, N, N> tril(const Array<T, true, N, N>& matrix)
{
    Array<T, true, N, N> lower_triangular;
    T zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column <= row; ++ column)
        {
            lower_triangular(row, column) = matrix(row, column);
        }
        for(int column = row+1; column < N; ++column)
        {
            lower_triangular(row, column) = zero_element;
        }
    }
    return lower_triangular;
}

template <int Low, int High, typename T, int FirstDim, int ... OtherDims>
Array<T, true, High-Low, OtherDims...> slice(const Array<T, true, FirstDim, OtherDims...>& array)
{
    Array<T, true, High-Low, OtherDims...> sliced;
    for(int index = Low; index < High; ++index)
    {
        sliced(index-Low) = array(index);
    }
    return sliced;
}
}