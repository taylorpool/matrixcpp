#pragma once

#include "sabai/products.hpp"

namespace sabai {

template <typename T> double norm(const DynamicVector<T> &vector) {
  return sqrt(dot(vector, vector));
}

template <typename T, uint64_t N>
double norm(const StaticVector<T, N> &vector) {
  return sqrt(static_cast<double>(dot(vector, vector)));
}
} // namespace sabai