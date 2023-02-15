#pragma once

namespace sabai {
template <typename T> constexpr T sum(T value) { return value; }

template <typename T, typename... Other>
constexpr T sum(T first, Other... others) {
  return first + sum(others...);
}

constexpr int product() { return 1; }

template <typename First, typename... Other>
constexpr int product(First first, Other... others) {
  return first * product(others...);
}
}; // namespace sabai