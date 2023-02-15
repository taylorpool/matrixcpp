#pragma once

#include "dynamic.hpp"
#include "static.hpp"

#include <sstream>

namespace sabai {
template <typename T> std::string to_str(const DynamicVector<T> &vector) {
  std::stringstream ss;
  for (int index = 0; index < vector.length(); ++index) {
    ss << vector(index) << " ";
  }
  return ss.str();
}

template <typename T> std::string to_str(const DynamicMatrix<T> &matrix) {
  std::stringstream ss;
  for (int row = 0; row < matrix.length(); ++row) {
    for (int col = 0; col < matrix(row).length(); ++col) {
      ss << matrix(row, col) << " ";
    }
    ss << std::endl;
  }
  return ss.str();
}

template <typename T, int N>
std::string to_str(const StaticVector<T, N> &vector) {
  std::stringstream ss;
  for (int index = 0; index < N; ++index) {
    ss << vector(index) << " ";
  }
  return ss.str();
}

template <typename T, int M, int N>
std::string to_str(const StaticArray<T, M, N> &matrix) {
  std::stringstream ss;
  for (int row = 0; row < M; ++row) {
    for (int col = 0; col < N; ++col) {
      ss << matrix(row, col) << " ";
    }
    ss << std::endl;
  }
  return ss.str();
}

} // namespace sabai