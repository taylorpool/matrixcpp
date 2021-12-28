#pragma once

#include "base.hpp"

namespace math
{
template <typename T, int N>
Array<T, N, N> triu(const Array<T, N, N>& matrix)
{
    Array<T, N, N> upper_triangular;
    for(int row = 0; row < N; ++row)
    {
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
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column <= row; ++ column)
        {
            lower_triangular(row, column) = matrix(row, column);
        }
    }
    return lower_triangular;
}
}