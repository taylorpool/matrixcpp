#pragma once

#include "sabai/dynamic.hpp"
#include "sabai/operators.hpp"
#include "sabai/static.hpp"

namespace sabai {

template <typename T>
DynamicVector<T> operator*(const T &value, const DynamicVector<T> &vector) {
  DynamicVector<T> answer = empty_like(vector);
  for (size_t index = static_cast<size_t>(0); index < vector.length();
       ++index) {
    answer(index) = value * vector(index);
  }
  return answer;
}

template <typename T, size_t Size>
StaticVector<T, Size> operator*(const T &value,
                                const StaticVector<T, Size> &vector) {
  StaticVector<T, Size> answer;
  for (size_t index = static_cast<size_t>(0); index < Size; ++index) {
    answer(index) = value * vector(index);
  }
  return answer;
}

template <typename T, size_t FirstDim, size_t SecondDim, size_t... OtherDims>
StaticArray<T, FirstDim, SecondDim, OtherDims...>
operator*(const T &value,
          const StaticArray<T, FirstDim, SecondDim, OtherDims...> &array) {
  auto answer = empty_like(array);
  for (size_t index = static_cast<size_t>(0); index < array.length(); ++index) {
    answer(index) = value * array(index);
  }
  return answer;
}

template <typename T, size_t NumDims>
DynamicArray<T, NumDims> operator*(const T &value,
                                   const DynamicArray<T, NumDims> &array) {
  auto answer = empty_like(array);
  for (size_t index = static_cast<size_t>(0); index < array.length(); ++index) {
    answer(index) = value * array(index);
  }
  return answer;
}

template <typename T>
DynamicVector<T> operator*(const DynamicVector<T> &vector, const T &value) {
  DynamicVector<T> answer = empty_like(vector);
  for (size_t index = static_cast<size_t>(0); index < vector.length();
       ++index) {
    answer(index) = vector(index) * value;
  }
  return answer;
}

template <typename T, size_t Size>
StaticVector<T, Size> operator*(const StaticVector<T, Size> &vector,
                                const T &value) {
  StaticVector<T, Size> answer;
  for (size_t index = static_cast<size_t>(0); index < Size; ++index) {
    answer(index) = vector(index) * value;
  }
  return answer;
}

template <typename T, size_t FirstDim, size_t SecondDim, size_t... OtherDims>
StaticArray<T, FirstDim, SecondDim, OtherDims...>
operator*(const StaticArray<T, FirstDim, SecondDim, OtherDims...> &array,
          const T &value) {
  auto answer = empty_like(array);
  for (size_t index = static_cast<size_t>(0); index < array.length(); ++index) {
    answer(index) = array(index) * value;
  }
  return answer;
}

template <typename T, size_t NumDims>
DynamicArray<T, NumDims> operator*(const DynamicArray<T, NumDims> &array,
                                   const T &value) {
  auto answer = empty_like(array);
  for (size_t index = static_cast<size_t>(0); index < array.length(); ++index) {
    answer(index) = array(index) * value;
  }
  return answer;
}

template <typename T>
T dot(const DynamicVector<T> &left, const DynamicVector<T> &right) {
  if (left.length() != right.length()) {
    throw MismatchedLength(left.length(), right.length());
  }
  T dot_product = static_cast<T>(0);
  for (size_t index = static_cast<size_t>(0); index < left.length(); ++index) {
    dot_product += left(index) * right(index);
  }
  return dot_product;
}

template <typename T, size_t M>
T dot(const StaticVector<T, M> &left, const StaticVector<T, M> &right) {
  T dot_product = static_cast<T>(0);
  for (size_t index = static_cast<size_t>(0); index < M; ++index) {
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
  if (left.length() != static_cast<size_t>(3)) {
    throw MismatchedLength(left.length(), static_cast<size_t>(3));
  } else if (right.length() != static_cast<size_t>(3)) {
    throw MismatchedLength(right.length(), static_cast<size_t>(3));
  }
  DynamicVector<T> result = empty_like(left);
  result(0) = left(1) * right(2) - left(2) * right(1);
  result(1) = left(2) * right(0) - left(0) * right(2);
  result(2) = left(0) * right(1) - left(1) * right(0);
  return result;
}

template <typename T, size_t M>
StaticMatrix<T, M, M> outer(const StaticVector<T, M> &left,
                            const StaticVector<T, M> &right) {
  StaticMatrix<T, M, M> result;
  for (size_t row = static_cast<size_t>(0); row < M; ++row) {
    for (size_t column = static_cast<size_t>(0); column < M; ++column) {
      result(row, column) = left(row) * right(column);
    }
  }
  return result;
}

template <typename T>
DynamicMatrix<T> outer(const DynamicVector<T> &left,
                       const DynamicVector<T> &right) {
  const size_t M = left.length();
  DynamicMatrix<T> result(M, M);
  for (size_t row = static_cast<size_t>(0); row < M; ++row) {
    for (size_t column = static_cast<size_t>(0); column < M; ++column) {
      result(row, column) = left(row) * right(column);
    }
  }
  return result;
}

template <typename T, size_t M, size_t N>
StaticVector<T, M> operator*(const StaticArray<T, M, N> &A,
                             const StaticVector<T, N> &x) {
  StaticVector<T, M> answer;
  for (size_t index = static_cast<size_t>(0); index < M; ++index) {
    answer(index) = dot(A(index), x);
  }
  return answer;
}

template <typename T>
DynamicVector<T> operator*(const DynamicMatrix<T> &A,
                           const DynamicVector<T> &x) {
  DynamicVector<T> answer(A.length());
  for (size_t index = static_cast<size_t>(0); index < answer.length();
       ++index) {
    answer(index) = dot(A(index), x);
  }
  return answer;
}

template <typename T>
DynamicMatrix<T> operator*(const DynamicMatrix<T> &left,
                           const DynamicMatrix<T> &right) {
  const size_t m = left.length();
  const size_t n = right.length();
  if (left(0).length() != n) {
    throw MismatchedLength(left(0).length(), n);
  }
  const size_t p = right(0).length();
  DynamicMatrix<T> result(m, p);
  for (size_t row = static_cast<size_t>(0); row < m; ++row) {
    for (size_t column = static_cast<size_t>(0); column < p; ++column) {
      result(row, column) = static_cast<T>(0);
      for (size_t index = static_cast<size_t>(0); index < n; ++index) {
        result(row, column) += left(row, index) * right(index, column);
      }
    }
  }
  return result;
}

template <typename T, size_t M, size_t N, size_t P>
StaticMatrix<T, M, P> operator*(const StaticMatrix<T, M, N> &left,
                                const StaticMatrix<T, N, P> &right) {
  auto answer = StaticArray<T, M, P>(static_cast<T>(0));
  for (size_t row = static_cast<size_t>(0); row < M; ++row) {
    for (size_t column = static_cast<size_t>(0); column < P; ++column) {
      for (size_t index = static_cast<size_t>(0); index < N; ++index) {
        answer(row, column) += left(row, index) * right(index, column);
      }
    }
  }
  return answer;
}
} // namespace sabai