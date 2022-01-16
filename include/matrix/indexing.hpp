#pragma once

#include "static.hpp"

namespace math
{
template <typename T, int N>
Array<T, N, N> triu(const Array<T, N, N>& matrix)
{
    Array<T, N, N> upper_triangular;
    auto zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column < row; ++ column)
        {
            upper_triangular(row, column) = zero_element;
        }
        for(int column = row; column < N; ++ column)
        {
            upper_triangular(row, column) = matrix(row, column);
        }
    }
    return upper_triangular;
}

template <typename T, int N>
Array<T, N, N> tril(const Array<T, N, N>& matrix)
{
    Array<T, N, N> lower_triangular;
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
Array<T, High-Low, OtherDims...> slice(const Array<T, FirstDim, OtherDims...>& array)
{
    Array<T, High-Low, OtherDims...> sliced;
    for(int index = Low; index < High; ++index)
    {
        sliced(index-Low) = array(index);
    }
    return sliced;
}
}