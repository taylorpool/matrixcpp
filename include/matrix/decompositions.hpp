#pragma once

#include "base.hpp"
#include "indexing.hpp"
#include "products.hpp"

#include <cmath>

namespace math
{
    template <typename T, int N>
    Array<T, N, N> cholesky(const Array<T, N, N>& A)
    {
        Array<T, N, N> U = triu(A);
        for(int i = 0; i < N; ++i)
        {
            for(int j = i+1; j < N; ++j)
            {
                T factor = U(i,j)/U(i,i);
                for(int k = j; k < N; ++k)
                {
                    U(j,k) = U(j,k) - U(i,k)*factor;
                }
            }
            T sqrt_factor = sqrt(U(i,i));
            for(int r = i; r < N; ++r)
            {
                U(i,i) = U(i,i)/sqrt_factor;
            }
        }
        return U;
    }

    template <typename T, int N>
    Vector<T, N> cholesky_solve(const Array<T, N, N>& chol, const Vector<T, N>& b)
    {
        Vector<T, N> y(b);
        for(int k = 0; k < N; ++k)
        {
            for(int j = 0; j < k; ++j)
            {
                y(k) -= chol(j,k)*y(j);
            }
            y(k) /= chol(k,k);
        }

        Vector<T, N> x(y);
        for(int k = N-1; k >= 0; --k)
        {
            for(int j = k+1; j < N; ++j)
            {
                x(k) -= chol(k,j)*x(j);
            }
            x(k) /= chol(k,k);
        }
        return x;
    }

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
                    T temp = U(k,j);
                    U(k,j) = U(i,j);
                    U(i,j) = temp;
                }
                for(int j = 0; j < k; ++j)
                {
                    T temp = L(k,j);
                    L(k,j) = L(i,j);
                    L(i,j) = temp;
                }
                int temp = P(k);
                P(k) = P(i);
                P(i) = temp;

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

    template <typename T, int M, int N>
    struct LUSolution
    {
        Vector<T, N> solution;
        Vector<T, M> y;

        LUSolution(const LUDecomposition<T, M, N>& lu_decomp, const Vector<T, M>& b)
        {

            Vector<T, M> Pb = b(lu_decomp.P);
            // Solve Ly = Pb via forward substitution
            for(int k = 0; k < M; ++k)
            {
                y(k) = Pb(k);
                for(int j = 0; j < k; ++j)
                {
                    y(k) -= lu_decomp.L(k,j)*y(j);
                }
            }
            // Solve Ux = y via backward substitution
            for(int k = N-1; k >= 0; --k)
            {
                solution(k) = y(k);
                for(int j = k+1; j < N; ++j)
                {
                    solution(k) -= lu_decomp.U(k,j)*solution(j);
                }
                solution(k) /= lu_decomp.U(k,k);
            }
        }
    };
}