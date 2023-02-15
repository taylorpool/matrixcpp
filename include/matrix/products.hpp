#pragma once

#include "dynamic.hpp"
#include "operators.hpp"
#include "static.hpp"

namespace math {

template <typename T>
DynamicVector<T> operator*(const T &value, const DynamicVector<T> &vector) {
  DynamicVector<T> answer = math::empty_like(vector);
  for (uint64_t index = 0; index < vector.length(); ++index) {
    answer(index) = value * vector(index);
  }
  return answer;
}

template <typename T, uint64_t Size>
StaticVector<T, Size> operator*(const T &value,
                                const StaticVector<T, Size> &vector) {
  StaticVector<T, Size> answer;
  for (uint64_t index = 0; index < Size; ++index) {
    answer(index) = value * vector(index);
  }
  return answer;
}

template <typename T, uint64_t FirstDim, uint64_t SecondDim,
          uint64_t... OtherDims>
StaticArray<T, FirstDim, SecondDim, OtherDims...>
operator*(const T &value,
          const StaticArray<T, FirstDim, SecondDim, OtherDims...> &array) {
  auto answer = empty_like(array);
  for (uint64_t index = 0; index < array.length(); ++index) {
    answer(index) = value * array(index);
  }
  return answer;
}

template <typename T, uint64_t NumDims>
DynamicArray<T, NumDims> operator*(const T &value,
                                   const DynamicArray<T, NumDims> &array) {
  auto answer = empty_like(array);
  for (uint64_t index = 0; index < array.length(); ++index) {
    answer(index) = value * array(index);
  }
  return answer;
}

template <typename T, bool IsStatic, uint64_t... Shape>
Array<T, IsStatic, Shape...> operator*(Array<T, IsStatic, Shape...> matrix,
                                       const T &value) {
  return value * matrix;
}

template <typename T>
T dot(const DynamicVector<T> &left, const DynamicVector<T> &right) {
  if (left.length() != right.length()) {
    throw MismatchedLength(left.length(), right.length());
  }
  T dot_product = static_cast<T>(0);
  for (uint64_t index = 0; index < left.length(); ++index) {
    dot_product += left(index) * right(index);
  }
  return dot_product;
}

template <typename T, uint64_t M>
T dot(const StaticVector<T, M> &left, const StaticVector<T, M> &right) {
  T dot_product = static_cast<T>(0);
  for (uint64_t index = 0; index < M; ++index) {
    dot_product += left(index) * right(index);
  }
  return dot_product;
}

template <typename T>
StaticVector<T, 3> cross(const StaticVector<T, 3> &left,
                         const StaticVector<T, 3> &right) {
  StaticVector<T, 3> result;
  result(0) = left(1) * right(2) - left(2) * right(1);
  result(1) = left(2) * right(0) - left(0) * right(2);
  result(2) = left(0) * right(1) - left(1) * right(0);
  return result;
}

template <typename T>
DynamicVector<T> cross(const DynamicVector<T> &left,
                       const DynamicVector<T> &right) {
  if (left.length() != 3) {
    throw MismatchedLength(left.length(), 3);
  } else if (right.length() != 3) {
    throw MismatchedLength(right.length(), 3);
  }
  DynamicVector<T> result = empty_like(left);
  result(0) = left(1) * right(2) - left(2) * right(1);
  result(1) = left(2) * right(0) - left(0) * right(2);
  result(2) = left(0) * right(1) - left(1) * right(0);
  return result;
}

template <typename T, uint64_t M>
StaticArray<T, M, M> outer(const StaticVector<T, M> &left,
                           const StaticVector<T, M> &right) {
  StaticArray<T, M, M> result;
  for (uint64_t row = 0; row < M; ++row) {
    for (uint64_t column = 0; column < M; ++column) {
      result(row, column) = left(row) * right(column);
    }
  }
  return result;
}

template <typename T>
DynamicMatrix<T> outer(const DynamicVector<T> &left,
                       const DynamicVector<T> &right) {
  const uint64_t M = left.length();
  DynamicMatrix<T> result(M, M);
  for (uint64_t row = 0; row < M; ++row) {
    for (uint64_t column = 0; column < M; ++column) {
      result(row, column) = left(row) * right(column);
    }
  }
  return result;
}

template <typename T, uint64_t M, uint64_t N>
StaticVector<T, M> operator*(const StaticArray<T, M, N> &A,
                             const StaticVector<T, N> &x) {
  StaticVector<T, M> answer;
  for (uint64_t index = 0; index < M; ++index) {
    answer(index) = dot(A(index), x);
  }
  return answer;
}

template <typename T>
DynamicVector<T> operator*(const DynamicMatrix<T> &A,
                           const DynamicVector<T> &x) {
  DynamicVector<T> answer(A.length());
  for (uint64_t index = 0; index < answer.length(); ++index) {
    answer(index) = dot(A(index), x);
  }
  return answer;
}

template <typename T>
DynamicMatrix<T> operator*(const DynamicMatrix<T> &left,
                           const DynamicMatrix<T> &right) {
  const uint64_t m = left.length();
  const uint64_t n = right.length();
  if (left(0).length() != n) {
    throw MismatchedLength(left(0).length(), n);
  }
  const uint64_t p = right(0).length();
  DynamicMatrix<T> result(m, p);
  for (uint64_t row = 0; row < m; ++row) {
    for (uint64_t column = 0; column < p; ++column) {
      result(row, column) = static_cast<T>(0);
      for (uint64_t index = 0; index < n; ++index) {
        result(row, column) += left(row, index) * right(index, column);
      }
    }
  }
  return result;
}

template <typename T, uint64_t M, uint64_t N, uint64_t P>
Array<T, true, M, P> operator*(const Array<T, true, M, N> &left,
                               const Array<T, true, N, P> &right) {
  auto answer = Array<T, true, M, P>(static_cast<T>(0));
  for (uint64_t row = 0; row < M; ++row) {
    for (uint64_t column = 0; column < P; ++column) {
      for (uint64_t index = 0; index < N; ++index) {
        answer(row, column) += left(row, index) * right(index, column);
      }
    }
  }
  return answer;
}
} // namespace math