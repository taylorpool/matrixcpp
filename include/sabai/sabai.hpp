#pragma once

#include <ranges>

namespace sabai {

template <typename T, size_t N> class VectorIterator {
public:
  using difference_type = ptrdiff_t;
  using value_type = T;
  using iterator_category = std::contiguous_iterator_tag;
  using element_type = T;

  T &operator*() const;
  T *operator->() const;
  T &operator[](const difference_type &) const;
};

template <typename T, size_t N>
VectorIterator<T, N> &operator++(VectorIterator<T, N> &);

template <typename T, size_t N>
VectorIterator<T, N> operator++(VectorIterator<T, N> &, int);

template <typename T, size_t N>
VectorIterator<T, N> &operator--(VectorIterator<T, N> &);

template <typename T, size_t N>
VectorIterator<T, N> operator--(VectorIterator<T, N> &, int);

template <typename T, size_t N>
bool operator==(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
bool operator!=(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
bool operator<(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
bool operator>(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
bool operator<=(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
bool operator>=(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
VectorIterator<T, N> &
operator+=(VectorIterator<T, N> &,
           const std::iter_difference_t<VectorIterator<T, N>> &);

template <typename T, size_t N>
VectorIterator<T, N>
operator+(const VectorIterator<T, N> &,
          const std::iter_difference_t<VectorIterator<T, N>> &);

template <typename T, size_t N>
VectorIterator<T, N>
operator+(const std::iter_difference_t<VectorIterator<T, N>> &,
          const VectorIterator<T, N> &);

template <typename T, size_t N>
VectorIterator<T, N> &
operator-=(VectorIterator<T, N> &,
           const std::iter_difference_t<VectorIterator<T, N>> &);

template <typename T, size_t N>
std::iter_difference_t<VectorIterator<T, N>>
operator-(const VectorIterator<T, N> &, const VectorIterator<T, N> &);

template <typename T, size_t N>
VectorIterator<T, N>
operator-(const VectorIterator<T, N> &,
          const std::iter_difference_t<VectorIterator<T, N>> &);

template <typename T, size_t N> class Vector {
public:
  T m_data[N];
};

template <typename T, size_t N>
VectorIterator<T, N> begin(const Vector<T, N> &) {
  VectorIterator<T, N> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T, N> end(const Vector<T, N> &) {
  VectorIterator<T, N> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T, N> begin(const Vector<T, N>) {
  VectorIterator<T, N> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T, N> end(const Vector<T, N>) {
  VectorIterator<T, N> iterator;
  return iterator;
}

} // namespace sabai