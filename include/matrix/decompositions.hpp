#pragma once

#include "dynamic.hpp"
#include "indexing.hpp"
#include "metrics.hpp"
#include "products.hpp"
#include "static.hpp"
#include "string_representation.hpp"

#include <iostream>

#include <cmath>

namespace math {
template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T> struct DynamicCholeskyDecomposition {
  DynamicMatrix<T> cholesky;

  DynamicCholeskyDecomposition(const DynamicMatrix<T> &A) : cholesky(triu(A)) {
    uint64_t N = A.length();
    for (uint64_t i = 0; i < N; ++i) {
      for (uint64_t j = i + 1; j < N; ++j) {
        const T factor = cholesky(i, j) / cholesky(i, i);
        for (uint64_t k = j; k < N; ++k) {
          cholesky(j, k) -= cholesky(i, k) * factor;
        }
      }
      const T sqrt_factor = sqrt(cholesky(i, i));
      for (uint64_t r = i; r < N; ++r) {
        cholesky(i, i) /= sqrt_factor;
      }
    }
  }
};

template <typename T, uint64_t N> struct CholeskyDecomposition {
  Array<T, true, N, N> cholesky;

  CholeskyDecomposition(const Array<T, true, N, N> &A) : cholesky(triu(A)) {
    for (uint64_t i = 0; i < N; ++i) {
      for (uint64_t j = i + 1; j < N; ++j) {
        const T factor = cholesky(i, j) / cholesky(i, i);
        for (uint64_t k = j; k < N; ++k) {
          cholesky(j, k) -= cholesky(i, k) * factor;
        }
      }
      const T sqrt_factor = sqrt(cholesky(i, i));
      for (uint64_t r = i; r < N; ++r) {
        cholesky(i, i) /= sqrt_factor;
      }
    }
  }
};

template <typename T> struct DynamicLUDecomposition {
  DynamicMatrix<T> L;
  DynamicMatrix<T> U;
  DynamicVector<uint64_t> P;

  DynamicLUDecomposition(const DynamicMatrix<T> &A)
      : U(A), L(Identity<T>(A.length())), P(ARange(A(0).length())) {
    const uint64_t M = A.length();
    const uint64_t N = A(0).length();
    for (uint64_t k = 0; k < N; ++k) {
      // Select index i>=k that maximizes std::abs(U(i,k))
      uint64_t i = k;
      T max_value = std::abs(U(i, k));
      for (uint64_t dummy_i = k; dummy_i < M; ++dummy_i) {
        const T value = std::abs(U(dummy_i, k));
        if (value > max_value) {
          i = dummy_i;
          max_value = value;
        }
      }
      for (uint64_t j = k; j < N; ++j) {
        swap(U(k, j), U(i, j));
      }
      for (uint64_t j = 0; j < k; ++j) {
        swap(L(k, j), L(i, j));
      }
      swap(P(k), P(i));

      for (uint64_t row = k + 1; row < M; ++row) {
        L(row, k) = U(row, k) / U(k, k);
        for (uint64_t column = k; column < N; ++column) {
          U(row, column) -= L(row, k) * U(k, column);
        }
      }
    }
  }
};

template <typename T, uint64_t M, uint64_t N> struct LUDecomposition {
  Array<T, true, M, M> L;
  Array<T, true, M, N> U;
  StaticVector<uint64_t, N> P;

  LUDecomposition(const Array<T, true, M, N> &A)
      : U(A), L(Identity<T, M>()), P(ARange<N>()) {
    for (uint64_t k = 0; k < N; ++k) {
      // Select index i>=k that maximizes std::abs(U(i,k))
      uint64_t i = k;
      T max_value = std::abs(U(i, k));
      for (int dummy_i = k; dummy_i < M; ++dummy_i) {
        const T value = std::abs(U(dummy_i, k));
        if (value > max_value) {
          i = dummy_i;
          max_value = value;
        }
      }
      for (uint64_t j = k; j < N; ++j) {
        swap(U(k, j), U(i, j));
      }
      for (uint64_t j = 0; j < k; ++j) {
        swap(L(k, j), L(i, j));
      }
      swap(P(k), P(i));

      for (uint64_t row = k + 1; row < M; ++row) {
        L(row, k) = U(row, k) / U(k, k);
        for (uint64_t column = k; column < N; ++column) {
          U(row, column) -= L(row, k) * U(k, column);
        }
      }
    }
  }
};

template <typename T, uint64_t M, uint64_t N> struct QRDecomposition {
  StaticArray<T, M, N> R;
  StaticArray<T, M, M> Q;

  QRDecomposition(const StaticArray<T, M, N> &A) : R(A), Q(Identity<T, M>()) {
    for (uint64_t k = 0; k < N; ++k) {
      DynamicVector<T> u(M - k);
      for (uint64_t i = k; i < R.length(); ++i) {
        u(i - k) = R(i, k);
      }
      const T norm_u = norm(u);
      u(0) += norm_u * (u(0) < 0 ? static_cast<T>(-1) : static_cast<T>(1));
      u /= norm(u);

      DynamicMatrix<T> U = outer(u, u);

      for (uint64_t i = k; i < M; ++i) {
        for (uint64_t j = k; j < N; ++j) {
          for (uint64_t s = 0; s < U.length(); ++s) {
            R(i, j) -= 2.0 * U(i - k, s) * R(s + k, j);
          }
        }
      }

      for (uint64_t i = k; i < M; ++i) {
        for (uint64_t j = 0; j < M; ++j) {
          for (uint64_t s = 0; s < U.length(); ++s) {
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
    const uint64_t m = A.length();
    const uint64_t n = A(0).length();
    for (uint64_t k = 0; k < n; ++k) {
      DynamicVector<T> u(m - k);
      for (uint64_t i = k; i < R.length(); ++i) {
        u(i - k) = R(i, k);
      }
      const T norm_u = norm(u);
      u(0) += norm_u * (u(0) < 0 ? static_cast<T>(-1) : static_cast<T>(1));
      u /= norm(u);

      DynamicMatrix<T> U = outer(u, u);

      for (uint64_t i = k; i < m; ++i) {
        for (uint64_t j = k; j < n; ++j) {
          for (uint64_t s = 0; s < U.length(); ++s) {
            R(i, j) -= 2.0 * U(i - k, s) * R(s + k, j);
          }
        }
      }

      for (uint64_t i = k; i < m; ++i) {
        for (uint64_t j = 0; j < m; ++j) {
          for (uint64_t s = 0; s < U.length(); ++s) {
            Q(i, j) -= 2.0 * U(i - k, s) * Q(s + k, j);
          }
        }
      }
    }
  }
};

template <typename T, uint64_t N>
StaticVector<T, N> forward_substitution_solve(const StaticMatrix<T, N, N> &A,
                                              const StaticVector<T, N> &b) {
  StaticVector<T, N> x(b);
  for (uint64_t index = 0; index < N; ++index) {
    for (uint64_t column = 0; column < index; ++column) {
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
  const uint64_t N = A.length();
  for (uint64_t index = 0; index < N; ++index) {
    for (uint64_t column = 0; column < index; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  return x;
}

template <typename T, uint64_t N>
StaticVector<T, N> backward_substitution_solve(const StaticMatrix<T, N, N> &A,
                                               const StaticVector<T, N> &b) {
  StaticVector<T, N> x(b);
  uint64_t index;
  for (index = N - 1; index > 0; --index) {
    for (uint64_t column = index + 1; column < N; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  for (uint64_t column = index + 1; column < N; ++column) {
    x(index) -= A(index, column) * x(column);
  }
  x(index) /= A(index, index);

  return x;
}

template <typename T>
DynamicVector<T> backward_substitution_solve(const DynamicMatrix<T> &A,
                                             const DynamicVector<T> &b) {
  DynamicVector<T> x(b);
  const uint64_t N = b.length();
  uint64_t index;
  for (index = N - 1; index > 0; --index) {
    for (uint64_t column = index + 1; column < N; ++column) {
      x(index) -= A(index, column) * x(column);
    }
    x(index) /= A(index, index);
  }
  for (uint64_t column = index + 1; column < N; ++column) {
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

template <typename T, uint64_t N>
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

template <typename T, uint64_t M, uint64_t N>
StaticVector<T, N> solve(const LUDecomposition<T, M, N> &lu_decomp,
                         const StaticVector<T, M> &b) {
  const StaticVector<T, M> Pb = b(lu_decomp.P);
  const StaticVector<T, M> y = forward_substitution_solve(lu_decomp.L, Pb);
  StaticVector<T, N> x = backward_substitution_solve(lu_decomp.U, y);
  return x;
}
} // namespace math