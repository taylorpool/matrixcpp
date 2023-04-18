#pragma once

#include "sabai/dynamic.hpp"
#include "sabai/indexing.hpp"
#include "sabai/metrics.hpp"
#include "sabai/products.hpp"
#include "sabai/static.hpp"
#include "sabai/string_representation.hpp"

#include <iostream>

#include <cmath>

namespace sabai {
template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T> struct DynamicCholeskyDecomposition {
  DynamicMatrix<T> cholesky;

  DynamicCholeskyDecomposition(const DynamicMatrix<T> &A) : cholesky(triu(A)) {
    const size_t N = A.length();
    for (size_t i = static_cast<size_t>(0); i < N; ++i) {
      for (size_t j = i + static_cast<size_t>(1); j < N; ++j) {
        const T factor = cholesky(i, j) / cholesky(i, i);
        for (size_t k = j; k < N; ++k) {
          cholesky(j, k) -= cholesky(i, k) * factor;
        }
      }
      const T sqrt_factor = sqrt(cholesky(i, i));
      for (size_t r = i; r < N; ++r) {
        cholesky(i, i) /= sqrt_factor;
      }
    }
  }
};

template <typename T, size_t N> struct CholeskyDecomposition {
  StaticArray<T, N, N> cholesky;

  CholeskyDecomposition(const StaticArray<T, N, N> &A) : cholesky(triu(A)) {
    for (size_t i = static_cast<size_t>(0); i < N; ++i) {
      for (size_t j = i + static_cast<size_t>(1); j < N; ++j) {
        const T factor = cholesky(i, j) / cholesky(i, i);
        for (size_t k = j; k < N; ++k) {
          cholesky(j, k) -= cholesky(i, k) * factor;
        }
      }
      const T sqrt_factor = sqrt(cholesky(i, i));
      for (size_t r = i; r < N; ++r) {
        cholesky(i, i) /= sqrt_factor;
      }
    }
  }
};

template <typename T> struct DynamicLUDecomposition {
  DynamicMatrix<T> L;
  DynamicMatrix<T> U;
  DynamicVector<size_t> P;

  DynamicLUDecomposition(const DynamicMatrix<T> &A)
      : U(A), L(Identity<T>(A.length())), P(ARange(A(0).length())) {
    const size_t M = A.length();
    const size_t N = A(0).length();
    for (size_t k = static_cast<size_t>(0); k < N; ++k) {
      // Select index i>=k that maximizes std::abs(U(i,k))
      size_t i = k;
      T max_value = std::abs(U(i, k));
      for (size_t dummy_i = k; dummy_i < M; ++dummy_i) {
        const T value = std::abs(U(dummy_i, k));
        if (value > max_value) {
          i = dummy_i;
          max_value = value;
        }
      }
      for (size_t j = k; j < N; ++j) {
        swap(U(k, j), U(i, j));
      }
      for (size_t j = static_cast<size_t>(0); j < k; ++j) {
        swap(L(k, j), L(i, j));
      }
      swap(P(k), P(i));

      for (size_t row = k + static_cast<size_t>(1); row < M; ++row) {
        L(row, k) = U(row, k) / U(k, k);
        for (size_t column = k; column < N; ++column) {
          U(row, column) -= L(row, k) * U(k, column);
        }
      }
    }
  }
};

template <typename T, size_t M, size_t N> struct LUDecomposition {
  StaticArray<T, M, M> L;
  StaticArray<T, M, N> U;
  StaticVector<size_t, N> P;

  LUDecomposition(const StaticArray<T, M, N> &A)
      : U(A), L(Identity<T, M>()), P(ARange<N>()) {
    for (size_t k = static_cast<size_t>(0); k < N; ++k) {
      // Select index i>=k that maximizes std::abs(U(i,k))
      size_t i = k;
      T max_value = std::abs(U(i, k));
      for (size_t dummy_i = k; dummy_i < M; ++dummy_i) {
        const T value = std::abs(U(dummy_i, k));
        if (value > max_value) {
          i = dummy_i;
          max_value = value;
        }
      }
      for (size_t j = k; j < N; ++j) {
        swap(U(k, j), U(i, j));
      }
      for (size_t j = static_cast<size_t>(0); j < k; ++j) {
        swap(L(k, j), L(i, j));
      }
      swap(P(k), P(i));

      for (size_t row = k + static_cast<size_t>(1); row < M; ++row) {
        L(row, k) = U(row, k) / U(k, k);
        for (size_t column = k; column < N; ++column) {
          U(row, column) -= L(row, k) * U(k, column);
        }
      }
    }
  }
};

template <typename T, size_t M, size_t N> struct QRDecomposition {
  StaticArray<T, M, N> R;
  StaticArray<T, M, M> Q;

  QRDecomposition(const StaticArray<T, M, N> &A) : R(A), Q(Identity<T, M>()) {
    for (size_t k = static_cast<size_t>(0); k < N; ++k) {
      DynamicVector<T> u(M - k);
      for (size_t i = k; i < R.length(); ++i) {
        u(i - k) = R(i, k);
      }
      const T norm_u = norm(u);
      u(0) += norm_u * (u(0) < 0 ? static_cast<T>(-1) : static_cast<T>(1));
      u /= norm(u);

      DynamicMatrix<T> U = outer(u, u);

      for (size_t i = k; i < M; ++i) {
        for (size_t j = k; j < N; ++j) {
          for (size_t s = static_cast<size_t>(0); s < U.length(); ++s) {
            R(i, j) -= 2.0 * U(i - k, s) * R(s + k, j);
          }
        }
      }

      for (size_t i = k; i < M; ++i) {
        for (size_t j = static_cast<size_t>(0); j < M; ++j) {
          for (size_t s = static_cast<size_t>(0); s < U.length(); ++s) {
            Q(i, j) -= 2.0 * U(i - k, s) * Q(s + k, j);
          }
        }
      }
    }
  }
};

template <typename T> struct DynamicQRDecomposition {
  DynamicMatrix<T> R;
  DynamicMatrix<T> Q;

  DynamicQRDecomposition(const DynamicMatrix<T> &A)
      : R(A), Q(Identity<T>(A.length())) {
    const size_t m = A.length();
    const size_t n = A(0).length();
    for (size_t k = static_cast<size_t>(0); k < n; ++k) {
      DynamicVector<T> u(m - k);
      for (size_t i = k; i < R.length(); ++i) {
        u(i - k) = R(i, k);
      }
      const T norm_u = norm(u);
      u(0) += norm_u * (u(0) < 0 ? static_cast<T>(-1) : static_cast<T>(1));
      u /= norm(u);

      DynamicMatrix<T> U = outer(u, u);

      for (size_t i = k; i < m; ++i) {
        for (size_t j = k; j < n; ++j) {
          for (size_t s = static_cast<size_t>(0); s < U.length(); ++s) {
            R(i, j) -= 2.0 * U(i - k, s) * R(s + k, j);
          }
        }
      }

      for (size_t i = k; i < m; ++i) {
        for (size_t j = 0; j < m; ++j) {
          for (size_t s = 0; s < U.length(); ++s) {
            Q(i, j) -= 2.0 * U(i - k, s) * Q(s + k, j);
          }
        }
      }
    }
  }
};

template <typename T, size_t N>
StaticVector<T, N> forward_substitution_solve(const StaticMatrix<T, N, N> &A,
                                              const StaticVector<T, N> &b) {
  StaticVector<T, N> x(b);
  for (size_t index = 0; index < N; ++index) {
    for (size_t column = 0; column < index; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  return x;
}

template <typename T>
DynamicVector<T> forward_substitution_solve(const DynamicMatrix<T> &A,
                                            const DynamicVector<T> &b) {
  DynamicVector<T> x(b);
  const size_t N = A.length();
  for (size_t index = 0; index < N; ++index) {
    for (size_t column = 0; column < index; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  return x;
}

template <typename T, size_t N>
StaticVector<T, N> backward_substitution_solve(const StaticMatrix<T, N, N> &A,
                                               const StaticVector<T, N> &b) {
  StaticVector<T, N> x(b);
  size_t index;
  for (index = N - 1; index > 0; --index) {
    for (size_t column = index + 1; column < N; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  for (size_t column = index + 1; column < N; ++column) {
    x(index) -= A(index, column) * x(column);
  }
  x(index) /= A(index, index);

  return x;
}

template <typename T>
DynamicVector<T> backward_substitution_solve(const DynamicMatrix<T> &A,
                                             const DynamicVector<T> &b) {
  DynamicVector<T> x(b);
  const size_t N = b.length();
  size_t index;
  for (index = N - 1; index > 0; --index) {
    for (size_t column = index + 1; column < N; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  for (size_t column = index + 1; column < N; ++column) {
    x(index) -= A(index, column) * x(column);
  }
  x(index) /= A(index, index);

  return x;
}

template <typename T>
DynamicVector<T> solve(const DynamicCholeskyDecomposition<T> &cholesky_decomp,
                       const DynamicVector<T> &b) {
  const DynamicVector<T> y =
      forward_substitution_solve(cholesky_decomp.cholesky, b);
  DynamicVector<T> x = backward_substitution_solve(cholesky_decomp.cholesky, y);
  return x;
}

template <typename T, size_t N>
StaticVector<T, N> solve(const CholeskyDecomposition<T, N> &cholesky_decomp,
                         const StaticVector<T, N> &b) {
  const StaticVector<T, N> y =
      forward_substitution_solve(cholesky_decomp.cholesky, b);
  StaticVector<T, N> x =
      backward_substitution_solve(cholesky_decomp.cholesky, y);
  return x;
}

template <typename T>
DynamicVector<T> solve(const DynamicLUDecomposition<T> &lu_decomp,
                       const DynamicVector<T> &b) {
  const DynamicVector<T> Pb = b(lu_decomp.P);
  const DynamicVector<T> y = forward_substitution_solve(lu_decomp.L, Pb);
  DynamicVector<T> x = backward_substitution_solve(lu_decomp.U, y);
  return x;
}

template <typename T, size_t M, size_t N>
StaticVector<T, N> solve(const LUDecomposition<T, M, N> &lu_decomp,
                         const StaticVector<T, M> &b) {
  const StaticVector<T, M> Pb = b(lu_decomp.P);
  const StaticVector<T, M> y = forward_substitution_solve(lu_decomp.L, Pb);
  StaticVector<T, N> x = backward_substitution_solve(lu_decomp.U, y);
  return x;
}
} // namespace sabai