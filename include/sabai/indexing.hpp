#pragma once

#include "sabai/dynamic.hpp"
#include "sabai/static.hpp"

namespace sabai {

template <typename T> DynamicMatrix<T> triu(const DynamicMatrix<T> &matrix) {
  const size_t N = matrix.length();
  DynamicMatrix<T> upper_triangular(N, N);
  const auto zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column < row; ++column) {
      upper_triangular(row, column) = zero_element;
    }
    for (size_t column = row; column < N; ++column) {
      upper_triangular(row, column) = matrix(row, column);
    }
  }
  return upper_triangular;
}

template <typename T, size_t N>
StaticMatrix<T, N, N> triu(const StaticMatrix<T, N, N> &matrix) {
  StaticMatrix<T, N, N> upper_triangular;
  const auto zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column < row; ++column) {
      upper_triangular(row, column) = zero_element;
    }
    for (size_t column = row; column < N; ++column) {
      upper_triangular(row, column) = matrix(row, column);
    }
  }
  return upper_triangular;
}

template <typename T> DynamicMatrix<T> tril(const DynamicMatrix<T> &matrix) {
  const size_t N = matrix.length();
  DynamicMatrix<T> lower_triangular(N, N);
  const auto zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column <= row; ++column) {
      lower_triangular(row, column) = matrix(row, column);
    }
    for (size_t column = row + static_cast<size_t>(1); column < N; ++column) {
      lower_triangular(row, column) = zero_element;
    }
  }
  return lower_triangular;
}

template <typename T, size_t N>
StaticMatrix<T, N, N> tril(const StaticMatrix<T, N, N> &matrix) {
  StaticMatrix<T, N, N> lower_triangular;
  const T zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column <= row; ++column) {
      lower_triangular(row, column) = matrix(row, column);
    }
    for (size_t column = row + static_cast<size_t>(1); column < N; ++column) {
      lower_triangular(row, column) = zero_element;
    }
  }
  return lower_triangular;
}

template <size_t Low, size_t High, typename T, size_t FirstDim,
          size_t... OtherDims>
StaticArray<T, High - Low, OtherDims...>
slice(const StaticArray<T, FirstDim, OtherDims...> &array) {
  StaticArray<T, High - Low, OtherDims...> sliced;
  for (size_t index = Low; index < High; ++index) {
    sliced(index - Low) = array(index);
  }
  return sliced;
}
} // namespace sabai