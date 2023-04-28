#pragma once

#include <ranges>

namespace sabai {

template <typename R, typename T>
concept input_range_of = std::ranges::input_range<R> &&
                         std::same_as<std::ranges::range_value_t<R>, T>;

template <typename T, size_t N> class Vector {
public:
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

  constexpr iterator begin() { return iterator(m_data); }
  constexpr iterator end() { return iterator(m_data + N); }
  constexpr const_iterator cbegin() { return const_iterator(m_data); }
  constexpr const_iterator cend() { return const_iterator(m_data + N); }

  constexpr T &operator[](size_type index) { return m_data[index]; }
  constexpr T &operator[](size_type index) const { return m_data[index]; }

  Vector(){};

  template <input_range_of<T> R> Vector(R &&range) {
    for (auto my_data = begin(), range_data = range.begin(); my_data != end();
         ++my_data, ++range_data) {
      *my_data = *range_data;
    }
  }
};

template <typename T, size_t N> constexpr auto operator+(Vector<T, N> &x, T y) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return value + y; });
}

template <typename T, size_t N> constexpr auto operator+(T y, Vector<T, N> &x) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return y + value; });
}

template <typename T, size_t N> constexpr auto operator-(Vector<T, N> &x, T y) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return value - y; });
}

template <typename T, size_t N> constexpr auto operator-(T y, Vector<T, N> &x) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return y - value; });
}

template <typename T, size_t N> constexpr auto operator*(Vector<T, N> &x, T y) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return value * y; });
}

template <typename T, size_t N> constexpr auto operator*(T y, Vector<T, N> &x) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return y * value; });
}

template <typename T, size_t N> constexpr auto operator-(Vector<T, N> &x) {
  return x |
         std::ranges::views::transform([](const T &value) { return -value; });
}

template <typename T, size_t N> constexpr auto operator/(Vector<T, N> &x, T y) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return value / y; });
}

template <typename T, size_t N> constexpr auto operator/(T y, Vector<T, N> &x) {
  return x | std::ranges::views::transform(
                 [y](const T &value) { return y / value; });
}

} // namespace sabai