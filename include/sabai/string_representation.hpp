#pragma once

#include "sabai/dynamic.hpp"
#include "sabai/static.hpp"

#include <sstream>

namespace sabai {
template <typename T> std::string to_str(const DynamicVector<T> &vector) {
  std::stringstream ss;
  for (size_t index = 0; index < vector.length(); ++index) {
    ss << vector(index) << " ";
  }
  return ss.str();
}

template <typename T> std::string to_str(const DynamicMatrix<T> &matrix) {
  std::stringstream ss;
  for (size_t row = 0; row < matrix.length(); ++row) {
    for (size_t col = 0; col < matrix(row).length(); ++col) {
      ss << matrix(row, col) << " ";
    }
    ss << std::endl;
  }
  return ss.str();
}

template <typename T, size_t N>
std::string to_str(const StaticVector<T, N> &vector) {
  std::stringstream ss;
  for (size_t index = 0; index < N; ++index) {
    ss << vector(index) << " ";
  }
  return ss.str();
}

template <typename T, size_t M, size_t N>
std::string to_str(const StaticMatrix<T, M, N> &matrix) {
  std::stringstream ss;
  for (size_t row = 0; row < M; ++row) {
    for (size_t col = 0; col < N; ++col) {
      ss << matrix(row, col) << " ";
    }
    ss << std::endl;
  }
  return ss.str();
}

} // namespace sabai