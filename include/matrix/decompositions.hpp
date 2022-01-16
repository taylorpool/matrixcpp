#pragma once

#include "static.hpp"
#include "indexing.hpp"
#include "products.hpp"

#include <cmath>

namespace math
{
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T, int N>
    struct CholeskyDecomposition
    {
        Array<T, N, N> cholesky;

        CholeskyDecomposition(const Array<T, N, N>& A)
        : cholesky(triu(A))
        {
            for(int i = 0; i < N; ++i)
            {
                for(int j = i+1; j < N; ++j)
                {
                    T factor = cholesky(i,j)/cholesky(i,i);
                    for(int k = j; k < N; ++k)
                    {
                        cholesky(j,k) -= cholesky(i,k)*factor;
                    }
                }
                T sqrt_factor = sqrt(cholesky(i,i));
                for(int r = i; r < N; ++r)
                {
                    cholesky(i,i) /= sqrt_factor;
                }
            }
        }
    };

    template <typename T, int M, int N>
    struct LUDecomposition
    {
        Array<T, M, M> L;
        Array<T, M, N> U;
        Vectori<N> P;

        LUDecomposition(const Array<T, M, N>& A)
        : U(A), L(Identity<T, M>()), P(ARange<N>())
        {
            for(int k = 0; k < N; ++k)
            {
                // Select index i>=k that maximizes abs(U(i,k))
                int i = k;
                T max_value = abs(U(i,k));
                for(int dummy_i = k; dummy_i < M; ++dummy_i)
                {
                    T value = abs(U(dummy_i,k));
                    if(value > max_value)
                    {
                        i = dummy_i;
                        max_value = value;
                    }
                }
                for(int j = k; j < N; ++j)
                {
                    swap(U(k,j), U(i,j));
                }
                for(int j = 0; j < k; ++j)
                {
                    swap(L(k,j), L(i,j));
                }
                swap(P(k), P(i));

                for(int row = k+1; row < M; ++row)
                {
                    L(row,k) = U(row,k)/U(k,k);
                    for(int column = k; column < N; ++column)
                    {
                        U(row,column) -= L(row,k)*U(k,column);
                    }
                }
            }
        }
    };

    template <typename T, int N>
    Vector<T, N> forward_substitution_solve(const Array<T, N, N>& A, const Vector<T, N>& b)
    {
        Vector<T, N> x(b);
        for(int index = 0; index < N; ++index)
        {
            for(int column = 0; column < index; ++column)
            {
                x(index) -= A(index,column)*x(column);
            }
            x(index) /= A(index,index);
        }
        return x;
    }

    template <typename T, int N>
    Vector<T, N> backward_substitution_solve(const Array<T, N, N>& A, const Vector<T, N>& b)
    {
        Vector<T, N> x(b);
        for(int index = N-1; index >= 0; --index)
        {
            for(int column = index+1; column < N; ++column)
            {
                x(index) -= A(index,column)*x(column);
            }
            x(index) /= A(index,index);
        }
        return x;
    }

    template <typename T, int N>
    Vector<T, N> solve(const CholeskyDecomposition<T, N>& cholesky_decomp, const Vector<T, N>& b)
    {
        Vector<T, N> y = forward_substitution_solve(cholesky_decomp.cholesky, b);
        Vector<T, N> x = backward_substitution_solve(cholesky_decomp.cholesky, y);
        return x;
    }

    template <typename T, int M, int N>
    Vector<T, N> solve(const LUDecomposition<T, M, N>& lu_decomp, const Vector<T, M>& b)
    {
        Vector<T, M> Pb = b(lu_decomp.P);
        Vector<T, M> y = forward_substitution_solve(lu_decomp.L, Pb);
        Vector<T, N> x = backward_substitution_solve(lu_decomp.U, y);
        return x;
    }
}