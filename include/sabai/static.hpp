#pragma once

#include "sabai/base.hpp"

#include <initializer_list>

namespace sabai {

template <typename T, size_t... Shape> class StaticArray;

template <typename T, size_t Dim> class StaticArray<T, Dim> {
protected:
  T data_[Dim];

  void check_input(size_t index) const {
    if (index >= Dim) {
      throw OutOfRange(index, Dim);
    }
  }

public:
  using InitializerList = std::initializer_list<T>;

  constexpr StaticArray(){};

  constexpr StaticArray(T initial_value) { fill(initial_value); }

  constexpr StaticArray(InitializerList values) {
    auto iter = values.begin();
    for (size_t index = static_cast<size_t>(0); index < values.size();
         ++index) {
      data_[index] = *iter;
      ++iter;
    }
  }

  constexpr StaticArray(const StaticArray &array) {
    for (size_t index = static_cast<size_t>(0); index < array.length();
         ++index) {
      data_[index] = array(index);
    }
  }

  constexpr void fill(T value) {
    for (size_t i = static_cast<size_t>(0); i < Dim; ++i) {
      data_[i] = value;
    }
  }

  constexpr T &operator()(size_t index) {
    check_input(index);
    return data_[index];
  }

  constexpr T operator()(size_t index) const {
    check_input(index);
    return data_[index];
  }

  template <size_t Size>
  constexpr StaticArray<T, Size>
  operator()(const StaticArray<size_t, Size> &indices) const {
    StaticArray<T, Size> indexed;
    for (size_t index = static_cast<size_t>(0); index < Size; ++index) {
      indexed(index) = data_[indices(index)];
    }
    return indexed;
  }

  constexpr void operator=(const StaticArray &array) {
    for (size_t index = static_cast<size_t>(0); index < array.length();
         ++index) {
      data_[index] = array(index);
    }
  }

  constexpr size_t length() const { return Dim; }
};

template <typename T, size_t FirstDim, size_t SecondDim, size_t... OtherDim>
class StaticArray<T, FirstDim, SecondDim, OtherDim...> {
protected:
  using SubArray = StaticArray<T, SecondDim, OtherDim...>;
  static constexpr size_t NumDims =
      static_cast<size_t>(2) + sizeof...(OtherDim);
  SubArray data_[FirstDim];

  constexpr void check_input(size_t index) const {
    if (index >= FirstDim || index < 0) {
      throw OutOfRange(index, FirstDim);
    }
  }

public:
  using InitializerList =
      std::initializer_list<typename SubArray::InitializerList>;

  constexpr StaticArray(){};

  constexpr StaticArray(T initial_value) { fill(initial_value); }

  constexpr StaticArray(InitializerList initializer_list) {
    size_t i = static_cast<size_t>(0);
    for (auto iter = initializer_list.begin(); iter != initializer_list.end();
         ++iter) {
      data_[i] = SubArray(*iter);
      ++i;
    }
  }

  constexpr StaticArray(const StaticArray &array) {
    for (size_t index = static_cast<size_t>(0); index < array.length();
         ++index) {
      data_[index] = array(index);
    }
  }

  constexpr void fill(T value) {
    for (size_t i = static_cast<size_t>(0); i < FirstDim; ++i) {
      data_[i].fill(value);
    }
  }

  constexpr void fill(const StaticArray &array) {
    for (size_t index = static_cast<size_t>(0); index < FirstDim; ++index) {
      data_[index].fill(array(index));
    }
  }

  constexpr SubArray &operator()(size_t index) {
    check_input(index);
    return data_[index];
  }

  constexpr SubArray operator()(size_t index) const {
    check_input(index);
    return data_[index];
  }

  template <typename... OtherIndices>
  constexpr auto operator()(size_t first, size_t second,
                            OtherIndices... others) const {
    check_input(first);
    return data_[first](second, others...);
  }

  template <typename... OtherIndices>
  constexpr auto &operator()(size_t first, size_t second,
                             OtherIndices... others) {
    check_input(first);
    return data_[first](second, others...);
  }

  template <size_t Size>
  constexpr StaticArray<T, Size, SecondDim, OtherDim...>
  operator()(const StaticArray<size_t, Size> &indices) const {
    StaticArray<T, Size, SecondDim, OtherDim...> indexed;
    for (size_t index = static_cast<size_t>(0); index < Size; ++index) {
      indexed(index) = data_[indices(index)];
    }
    return indexed;
  }

  constexpr void operator=(const StaticArray &array) {
    for (size_t index = static_cast<size_t>(0); index < array.length();
         ++index) {
      data_[index] = array(index);
    }
  }

  constexpr size_t length() const { return FirstDim; }
};

template <size_t... Shape> using StaticArrayi = StaticArray<int, Shape...>;

template <size_t... Shape> using StaticArrayf = StaticArray<float, Shape...>;

template <size_t... Shape> using StaticArrayd = StaticArray<double, Shape...>;

template <typename T, size_t Size> using StaticVector = StaticArray<T, Size>;

template <size_t Size> using StaticVectori = StaticVector<int, Size>;

template <size_t Size> using StaticVectorf = StaticVector<float, Size>;

template <size_t Size> using StaticVectord = StaticVector<double, Size>;

template <typename T, size_t M, size_t N>
using StaticMatrix = StaticArray<T, M, N>;

template <size_t M, size_t N> using StaticMatrixi = StaticMatrix<int, M, N>;

template <size_t M, size_t N> using StaticMatrixf = StaticMatrix<float, M, N>;

template <size_t M, size_t N> using StaticMatrixd = StaticMatrix<double, M, N>;

template <typename T, typename V = T, size_t... Shape>
constexpr StaticArray<V, Shape...>
empty_like(const StaticArray<T, Shape...> &array) {
  return StaticArray<V, Shape...>();
}

template <typename T, size_t Length>
constexpr bool all_equal(const StaticVector<T, Length> &left,
                         const StaticVector<T, Length> &right) {
  for (size_t index = static_cast<size_t>(0); index < left.length(); ++index) {
    if (left(index) != right(index)) {
      return false;
    }
  }
  return true;
}

template <typename T, size_t Length1, size_t Length2, size_t... Lengths>
constexpr bool
all_equal(const StaticArray<T, Length1, Length2, Lengths...> &left,
          const StaticArray<T, Length1, Length2, Lengths...> &right) {
  for (size_t index = static_cast<size_t>(0); index < left.length(); ++index) {
    if (!all_equal(left(index), right(index))) {
      return false;
    }
  }
  return true;
}

template <size_t Length>
constexpr bool all(const StaticVector<bool, Length> &vector) {
  for (size_t index = 0; index < vector.length(); ++index) {
    if (!vector(index)) {
      return false;
    }
  }
  return true;
}

template <size_t FirstLength, size_t SecondLength, size_t... Shape>
constexpr bool
all(const StaticArray<bool, FirstLength, SecondLength, Shape...> &array) {
  for (size_t index = static_cast<size_t>(0); index < array.length(); ++index) {
    if (!all(array(index))) {
      return false;
    }
  }
  return true;
}

template <typename T, size_t N> constexpr StaticMatrix<T, N, N> Identity() {
  StaticMatrix<T, N, N> matrix;
  const T identity_element = static_cast<T>(1);
  const T zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column < N; ++column) {
      matrix(row, column) = (row == column ? identity_element : zero_element);
    }
  }
  return matrix;
}

template <size_t N> constexpr StaticVector<size_t, N> ARange() {
  StaticVector<size_t, N> range;
  for (size_t index = static_cast<size_t>(0); index < N; ++index) {
    range(index) = index;
  }
  return range;
}
} // namespace sabai