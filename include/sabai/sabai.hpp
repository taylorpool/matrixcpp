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

template <typename T>
bool operator==(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
bool operator!=(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
bool operator<(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
bool operator>(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
bool operator<=(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
bool operator>=(const VectorIterator<T> &, const VectorIterator<T> &);

template <typename T>
VectorIterator<T> &
operator+=(VectorIterator<T> &,
           const std::iter_difference_t<VectorIterator<T>> &);

template <typename T>
VectorIterator<T> operator+(const VectorIterator<T> &,
                            const std::iter_difference_t<VectorIterator<T>> &);

template <typename T>
VectorIterator<T> operator+(const std::iter_difference_t<VectorIterator<T>> &,
                            const VectorIterator<T> &);

template <typename T>
VectorIterator<T> &
operator-=(VectorIterator<T> &,
           const std::iter_difference_t<VectorIterator<T>> &);

template <typename T>
std::iter_difference_t<VectorIterator<T>> operator-(const VectorIterator<T> &,
                                                    const VectorIterator<T> &);

template <typename T>
VectorIterator<T> operator-(const VectorIterator<T> &,
                            const std::iter_difference_t<VectorIterator<T>> &);

template <typename T, size_t N> class Vector {
public:
  T m_data[N];
};

template <typename T, size_t N> VectorIterator<T> begin(const Vector<T, N> &) {
  VectorIterator<T> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T> end(const Vector<T, N> &) {
  VectorIterator<T> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T> begin(const Vector<T, N>) {
  VectorIterator<T> iterator;
  return iterator;
}

template <typename T, size_t N> VectorIterator<T> end(const Vector<T, N>) {
  VectorIterator<T> iterator;
  return iterator;
}

} // namespace sabai