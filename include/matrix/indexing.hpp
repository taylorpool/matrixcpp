#pragma once

#include "dynamic.hpp"
#include "static.hpp"

namespace math {

template <typename T> DynamicMatrix<T> triu(const DynamicMatrix<T> &matrix) {
  const uint64_t N = matrix.length();
  DynamicMatrix<T> upper_triangular(N, N);
  const auto zero_element = static_cast<T>(0);
  for (int row = 0; row < N; ++row) {
    for (int column = 0; column < row; ++column) {
      upper_triangular(row, column) = zero_element;
    }
    for (int column = row; column < N; ++column) {
      upper_triangular(row, column) = matrix(row, column);
    }
  }
  return upper_triangular;
}

template <typename T, uint64_t N>
Array<T, true, N, N> triu(const Array<T, true, N, N> &matrix) {
  Array<T, true, N, N> upper_triangular;
  const auto zero_element = static_cast<T>(0);
  for (uint64_t row = 0; row < N; ++row) {
    for (uint64_t column = 0; column < row; ++column) {
      upper_triangular(row, column) = zero_element;
    }
    for (uint64_t column = row; column < N; ++column) {
      upper_triangular(row, column) = matrix(row, column);
    }
  }
  return upper_triangular;
}

template <typename T> DynamicMatrix<T> tril(const DynamicMatrix<T> &matrix) {
  const uint64_t N = matrix.length();
  DynamicMatrix<T> lower_triangular(N, N);
  const auto zero_element = static_cast<T>(0);
  for (uint64_t row = 0; row < N; ++row) {
    for (uint64_t column = 0; column <= row; ++column) {
      lower_triangular(row, column) = matrix(row, column);
    }
    for (uint64_t column = row + 1; column < N; ++column) {
      lower_triangular(row, column) = zero_element;
    }
  }
  return lower_triangular;
}

template <typename T, uint64_t N>
Array<T, true, N, N> tril(const Array<T, true, N, N> &matrix) {
  Array<T, true, N, N> lower_triangular;
  const T zero_element = static_cast<T>(0);
  for (uint64_t row = 0; row < N; ++row) {
    for (uint64_t column = 0; column <= row; ++column) {
      lower_triangular(row, column) = matrix(row, column);
    }
    for (uint64_t column = row + 1; column < N; ++column) {
      lower_triangular(row, column) = zero_element;
    }
  }
  return lower_triangular;
}

template <uint64_t Low, uint64_t High, typename T, uint64_t FirstDim,
          uint64_t... OtherDims>
Array<T, true, High - Low, OtherDims...>
slice(const Array<T, true, FirstDim, OtherDims...> &array) {
  Array<T, true, High - Low, OtherDims...> sliced;
  for (uint64_t index = Low; index < High; ++index) {
    sliced(index - Low) = array(index);
  }
  return sliced;
}
} // namespace math