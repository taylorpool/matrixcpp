#pragma once

#include "base.hpp"

namespace math
{
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
                sum += left(row,index)*right(index,column);
            }
            answer(row,column) = sum;
        }
    }
    return answer;
}
}