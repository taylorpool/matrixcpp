#pragma once

#include "static.hpp"
#include "dynamic.hpp"
#include "indexing.hpp"
#include "products.hpp"
#include "metrics.hpp"
#include "string_representation.hpp"

#include <iostream>

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

    template <typename T>
    struct DynamicCholeskyDecomposition
    {
        DynamicMatrix<T> cholesky;

        DynamicCholeskyDecomposition(const DynamicMatrix<T>& A)
        : cholesky(triu(A))
        {
            int N = A.length();
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

    template <typename T, int N>
    struct CholeskyDecomposition
    {
        Array<T, true, N, N> cholesky;

        CholeskyDecomposition(const Array<T, true, N, N>& A)
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

    template <typename T>
    struct DynamicLUDecomposition
    {
        DynamicMatrix<T> L;
        DynamicMatrix<T> U;
        DynamicVectori P;

        DynamicLUDecomposition(const DynamicMatrix<T>& A)
        : U(A), L(Identity<T>(A.length())), P(ARange(A(0).length()))
        {
            int M = A.length();
            int N = A(0).length();
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

    template <typename T, int M, int N>
    struct LUDecomposition
    {
        Array<T, true, M, M> L;
        Array<T, true, M, N> U;
        StaticVectori<N> P;

        LUDecomposition(const Array<T, true, M, N>& A)
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

    template <typename T, int M, int N>
    struct QRDecomposition
    {
        StaticArray<T,M,N> R;
        StaticArray<T,M,M> Q;

        QRDecomposition(const StaticArray<T,M,N>& A)
        : R(A), Q(Identity<T,M>())
        {
            for(int k = 0; k < N; ++k)
            {
                DynamicVector<T> u(M-k);
                for(int i = k; i < R.length(); ++i)
                {
                    u(i-k) = R(i,k);
                }
                T norm_u = norm(u);
                u(0) += norm_u*(u(0) < 0 ? static_cast<T>(-1) : static_cast<T>(1));
                u /= norm(u);

                DynamicMatrix<T> U = outer(u, u);

                for(int i = k; i < M; ++i)
                {
                    for(int j = k; j < N; ++j)
                    {
                        for(int s = 0; s < U.length(); ++s)
                        {
                            R(i,j) -= 2.0*U(i-k,s)*R(s+k,j);
                        }
                    }
                }

                for(int i = k; i < M; ++i)
                {
                    for(int j = 0; j < M; ++j)
                    {
                        for(int s = 0; s < U.length(); ++s)
                        {
                            Q(i,j) -= 2.0*U(i-k,s)*Q(s+k,j);
                        }
                    }
                }
            }
        }
    };

    template <typename T, int N>
    StaticVector<T, N> forward_substitution_solve(const Array<T, true, N, N>& A, const StaticVector<T, N>& b)
    {
        StaticVector<T, N> x(b);
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

    template <typename T>
    DynamicVector<T> forward_substitution_solve(const DynamicMatrix<T>& A, const DynamicVector<T>& b)
    {
        DynamicVector<T> x(b);
        int N = A.length();
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
    StaticVector<T, N> backward_substitution_solve(const Array<T, true, N, N>& A, const StaticVector<T, N>& b)
    {
        StaticVector<T, N> x(b);
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

    template <typename T>
    DynamicVector<T> backward_substitution_solve(const DynamicMatrix<T>& A, const DynamicVector<T>&b)
    {
        DynamicVector<T> x(b);
        int N = b.length();
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

    template <typename T>
    DynamicVector<T> solve(const DynamicCholeskyDecomposition<T>& cholesky_decomp, const DynamicVector<T>& b)
    {
        DynamicVector<T> y = forward_substitution_solve(cholesky_decomp.cholesky, b);
        DynamicVector<T> x = backward_substitution_solve(cholesky_decomp.cholesky, y);
        return x;
    }

    template <typename T, int N>
    StaticVector<T, N> solve(const CholeskyDecomposition<T, N>& cholesky_decomp, const StaticVector<T, N>& b)
    {
        StaticVector<T, N> y = forward_substitution_solve(cholesky_decomp.cholesky, b);
        StaticVector<T, N> x = backward_substitution_solve(cholesky_decomp.cholesky, y);
        return x;
    }

    template <typename T>
    DynamicVector<T> solve(const DynamicLUDecomposition<T>& lu_decomp, const DynamicVector<T>& b)
    {
        DynamicVector<T> Pb = b(lu_decomp.P);
        DynamicVector<T> y = forward_substitution_solve(lu_decomp.L, Pb);
        DynamicVector<T> x = backward_substitution_solve(lu_decomp.U, y);
        return x;
    }

    template <typename T, int M, int N>
    StaticVector<T, N> solve(const LUDecomposition<T, M, N>& lu_decomp, const StaticVector<T, M>& b)
    {
        StaticVector<T, M> Pb = b(lu_decomp.P);
        StaticVector<T, M> y = forward_substitution_solve(lu_decomp.L, Pb);
        StaticVector<T, N> x = backward_substitution_solve(lu_decomp.U, y);
        return x;
    }
}