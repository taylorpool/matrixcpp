#pragma once

#include "sabai/base.hpp"
#include "sabai/dynamic.hpp"
#include "sabai/static.hpp"
#include <cmath>

namespace sabai {

template <typename T, size_t... Shape>
StaticArray<bool, Shape...> operator==(const StaticArray<T, Shape...> &left,
                                       const StaticArray<T, Shape...> &right) {
  StaticArray<bool, Shape...> result = empty_like<T, bool>(left);
  for (size_t index = 0; index < result.length(); ++index) {
    result(index) = (left(index) == right(index));
  }
  return result;
}

template <size_t... Shape>
StaticArray<bool, Shape...>
operator!(const StaticArray<bool, Shape...> &array) {
  StaticArray<bool, Shape...> result = empty_like(array);
  for (size_t index = 0; index < result.length(); ++index) {
    result(index) = !array(index);
  }
  return result;
}

template <typename T, size_t... Shape>
StaticArray<bool, Shape...> operator!=(const StaticArray<T, Shape...> &left,
                                       const StaticArray<T, Shape...> &right) {
  return !(left == right);
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...> operator-(const StaticArray<T, Shape...> &array) {
  auto negative_array = empty_like(array);
  for (size_t index = 0; index < negative_array.length(); ++index) {
    negative_array(index) = -array(index);
  }
  return negative_array;
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...> operator+(const StaticArray<T, Shape...> &left,
                                   const StaticArray<T, Shape...> &right) {
  auto summed = empty_like(left);
  for (size_t index = 0; index < summed.length(); ++index) {
    summed(index) = left(index) + right(index);
  }
  return summed;
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...> operator-(const StaticArray<T, Shape...> &left,
                                   const StaticArray<T, Shape...> &right) {
  auto summed = empty_like(left);
  for (size_t index = 0; index < summed.length(); ++index) {
    summed(index) = left(index) - right(index);
  }
  return summed;
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...>
operator/(const T &numerator, const StaticArray<T, Shape...> &denominator) {
  auto result = empty_like(denominator);
  for (size_t index = 0; index < denominator.length(); ++index) {
    result(index) = numerator / denominator(index);
  }
  return result;
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...> operator/(const StaticArray<T, Shape...> &numerator,
                                   T divisor) {
  auto divided = empty_like(numerator);
  for (size_t index = 0; index < divided.length(); ++index) {
    divided(index) = numerator(index) / divisor;
  }
  return divided;
}

template <typename T, size_t... Shape>
StaticArray<T, Shape...> operator/=(StaticArray<T, Shape...> &array,
                                    T divisor) {
  for (size_t index = 0; index < array.length(); ++index) {
    array(index) /= divisor;
  }
  return array;
}

template <typename T, size_t Dim>
DynamicArray<bool, Dim> operator==(const DynamicArray<T, Dim> &left,
                                   const DynamicArray<T, Dim> &right) {
  DynamicArray<bool, Dim> result = empty_like<T, bool>(left);
  for (size_t index = 0; index < result.length(); ++index) {
    result(index) = (left(index) == right(index));
  }
  return result;
}

template <size_t Dim>
DynamicArray<bool, Dim> operator!(const DynamicArray<bool, Dim> &array) {
  DynamicArray<bool, Dim> result = empty_like(array);
  for (size_t index = 0; index < result.length(); ++index) {
    result(index) = !array(index);
  }
  return result;
}

template <typename T, size_t Dim>
DynamicArray<bool, Dim> operator!=(const DynamicArray<T, Dim> &left,
                                   const DynamicArray<T, Dim> &right) {
  return !(left == right);
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator-(const DynamicArray<T, Dim> &array) {
  auto negative_array = empty_like(array);
  for (size_t index = 0; index < negative_array.length(); ++index) {
    negative_array(index) = -array(index);
  }
  return negative_array;
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator+(const DynamicArray<T, Dim> &left,
                               const DynamicArray<T, Dim> &right) {
  auto summed = empty_like(left);
  for (size_t index = 0; index < summed.length(); ++index) {
    summed(index) = left(index) + right(index);
  }
  return summed;
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator-(const DynamicArray<T, Dim> &left,
                               const DynamicArray<T, Dim> &right) {
  auto summed = empty_like(left);
  for (size_t index = 0; index < summed.length(); ++index) {
    summed(index) = left(index) - right(index);
  }
  return summed;
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator/(const T &numerator,
                               const DynamicArray<T, Dim> &denominator) {
  auto result = empty_like(denominator);
  for (size_t index = 0; index < denominator.length(); ++index) {
    result(index) = numerator / denominator(index);
  }
  return result;
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator/(const DynamicArray<T, Dim> &numerator,
                               T divisor) {
  auto divided = empty_like(numerator);
  for (size_t index = 0; index < divided.length(); ++index) {
    divided(index) = numerator(index) / divisor;
  }
  return divided;
}

template <typename T, size_t Dim>
DynamicArray<T, Dim> operator/=(DynamicArray<T, Dim> &array, T divisor) {
  for (size_t index = 0; index < array.length(); ++index) {
    array(index) /= divisor;
  }
  return array;
}

template <typename T, size_t N> T sum(const StaticVector<T, N> &vector) {
  T summation = vector(0);
  for (size_t index = 1; index < N; ++index) {
    summation += vector(index);
  }
  return summation;
}

} // namespace sabai