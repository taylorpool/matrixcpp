#pragma once

#include <exception>
#include <ranges>

class MisMatchedSize : public std::exception {
public:
  const char *what() const noexcept override { return "mismatched sizes"; }
};

class IndexOutOfRange : public std::exception {
public:
  const char *what() const noexcept override { return "index out of range"; }
};

namespace sabai {

template <typename R, typename T>
concept input_range_of = std::ranges::input_range<R> &&
    std::same_as<std::ranges::range_value_t<R>, T>;

template <typename R, typename T>
concept range_of = std::same_as<std::ranges::range_value_t<R>, T>;

template <typename R>
concept VectorConcept = R::isVector;

template <typename R, typename T>
concept TypedVectorConcept = range_of<R, T> && VectorConcept<R>;

template <typename R> struct Range : public R {
  static constexpr bool isVector = true;
};

template <typename T, size_t N> class Vector {
public:
  static constexpr bool isVector = true;
  using value_type = T;
  using pointer = T *;
  using const_pointer = const pointer;
  using reference = value_type &;
  using const_reference = const reference;
  using iterator = pointer;
  using const_iterator = const iterator;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  T m_data[N];

  constexpr iterator begin() noexcept { return iterator(m_data); }
  constexpr iterator end() noexcept { return iterator(m_data + N); }
  static constexpr size_t size() noexcept { return N; }
  constexpr const_iterator cbegin() const noexcept {
    return const_iterator(m_data);
  }
  constexpr const_iterator cend() const noexcept {
    return const_iterator(m_data + N);
  }

  constexpr T &operator[](size_type index) {
    if (index >= size()) {
      throw(IndexOutOfRange());
    }
    return m_data[index];
  }
  constexpr T &operator[](size_type index) const {
    if (index >= size()) {
      throw(IndexOutOfRange());
    }
    return m_data[index];
  }

  constexpr Vector(){};
  template <input_range_of<T> R> constexpr Vector(R &&range) {
    if (range.size() != size()) {
      throw(MisMatchedSize());
    }

    for (auto my_data = begin(), range_data = range.begin();
         my_data != end() && range_data != range.end();
         ++my_data, ++range_data) {
      *my_data = *range_data;
    }
  }

  template <range_of<T> R> constexpr Vector(R &&range) {
    if (range.size() != size()) {
      throw(MisMatchedSize());
    }

    for (auto my_data = begin(), range_data = range.begin();
         my_data != end() && range_data != range.end();
         ++my_data, ++range_data) {
      *my_data = *range_data;
    }
  }
};

template <size_t N> using Vectori = Vector<int, N>;

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator+(X &x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value + y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator+(X &&x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value + y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator+(T y, X &x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y + value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator+(T y, X &&x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y + value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator-(X &x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value - y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator-(X &&x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value - y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator-(T y, X &x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y - value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator-(T y, X &&x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y - value; })};
}

template <VectorConcept X> constexpr auto operator-(X &x) {
  return Range{x | std::ranges::views::transform(
                       [](const std::ranges::range_value_t<X> &value) {
                         return -value;
                       })};
}

template <VectorConcept X> constexpr auto operator-(X &&x) {
  return Range{x | std::ranges::views::transform(
                       [](const std::ranges::range_value_t<X> &value) {
                         return -value;
                       })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator*(X &x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value * y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator*(X &&x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value * y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator*(T y, X &x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y * value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator*(T y, X &&x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y * value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator/(X &x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value / y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator/(X &&x, T y) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return value / y; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator/(T y, X &x) {
  return Range{x | std::ranges::views::transform(
                       [y](const T &value) { return y / value; })};
}

template <typename T, TypedVectorConcept<T> X>
constexpr auto operator/(T y, X &&x) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return y / value; });
}

} // namespace sabai