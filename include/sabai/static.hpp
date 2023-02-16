#pragma once

#include "sabai/base.hpp"

#include <initializer_list>

namespace sabai {

template <typename T, uint64_t Dim> class Array<T, true, Dim> {
private:
  T data_[Dim];

  void check_input(uint64_t index) const {
    if (index >= Dim) {
      throw OutOfRange(index, Dim);
    }
  }

public:
  using InitializerList = std::initializer_list<T>;

  constexpr Array(){};

  constexpr Array(T initial_value) { fill(initial_value); }

  constexpr Array(InitializerList values) {
    auto iter = values.begin();
    for (uint64_t index = 0; index < values.size(); ++index) {
      data_[index] = *iter;
      ++iter;
    }
  }

  constexpr Array(const Array &array) {
    for (uint64_t index = 0; index < array.length(); ++index) {
      data_[index] = array(index);
    }
  }

  constexpr void fill(T value) {
    for (int i = 0; i < Dim; ++i) {
      data_[i] = value;
    }
  }

  constexpr T &operator()(uint64_t index) {
    check_input(index);
    return data_[index];
  }

  constexpr T operator()(uint64_t index) const {
    check_input(index);
    return data_[index];
  }

  template <uint64_t Size>
  constexpr Array<T, true, Size>
  operator()(const Array<uint64_t, true, Size> &indices) const {
    Array<T, true, Size> indexed;
    for (uint64_t index = 0; index < Size; ++index) {
      indexed(index) = data_[indices(index)];
    }
    return indexed;
  }

  constexpr void operator=(const Array &array) {
    for (uint64_t index = 0; index < array.length(); ++index) {
      data_[index] = array(index);
    }
  }

  constexpr uint64_t length() const { return Dim; }
};

template <typename T, uint64_t FirstDim, uint64_t SecondDim,
          uint64_t... OtherDim>
class Array<T, true, FirstDim, SecondDim, OtherDim...> {
private:
  using SubArray = Array<T, true, SecondDim, OtherDim...>;
  static constexpr uint64_t NumDims = 2 + sizeof...(OtherDim);
  SubArray data_[FirstDim];

  constexpr void check_input(uint64_t index) const {
    if (index >= FirstDim || index < 0) {
      throw OutOfRange(index, FirstDim);
    }
  }

public:
  using InitializerList =
      std::initializer_list<typename SubArray::InitializerList>;

  constexpr Array(){};

  constexpr Array(T initial_value) { fill(initial_value); }

  constexpr Array(InitializerList initializer_list) {
    uint64_t i = 0;
    for (auto iter = initializer_list.begin(); iter != initializer_list.end();
         ++iter) {
      data_[i] = SubArray(*iter);
      ++i;
    }
  }

  constexpr Array(const Array &array) {
    for (uint64_t index = 0; index < array.length(); ++index) {
      data_[index] = array(index);
    }
  }

  constexpr void fill(T value) {
    for (uint64_t i = 0; i < FirstDim; ++i) {
      data_[i].fill(value);
    }
  }

  constexpr void fill(const Array &array) {
    for (uint64_t index = 0; index < FirstDim; ++index) {
      data_[index].fill(array(index));
    }
  }

  constexpr SubArray &operator()(uint64_t index) {
    check_input(index);
    return data_[index];
  }

  constexpr SubArray operator()(uint64_t index) const {
    check_input(index);
    return data_[index];
  }

  template <typename... OtherIndices>
  constexpr auto operator()(uint64_t first, uint64_t second,
                            OtherIndices... others) const {
    check_input(first);
    return data_[first](second, others...);
  }

  template <typename... OtherIndices>
  constexpr auto &operator()(uint64_t first, uint64_t second,
                             OtherIndices... others) {
    check_input(first);
    return data_[first](second, others...);
  }

  template <uint64_t Size>
  constexpr Array<T, true, Size, SecondDim, OtherDim...>
  operator()(const Array<uint64_t, true, Size> &indices) const {
    Array<T, true, Size, SecondDim, OtherDim...> indexed;
    for (uint64_t index = 0; index < Size; ++index) {
      indexed(index) = data_[indices(index)];
    }
    return indexed;
  }

  constexpr void operator=(const Array &array) {
    for (int index = 0; index < array.length(); ++index) {
      data_[index] = array(index);
    }
  }

  constexpr uint64_t length() const { return FirstDim; }
};

template <typename T, uint64_t... Shape>
using StaticArray = Array<T, true, Shape...>;

template <uint64_t... Shape> using StaticArrayi = StaticArray<int, Shape...>;

template <uint64_t... Shape> using StaticArrayf = StaticArray<float, Shape...>;

template <uint64_t... Shape> using StaticArrayd = StaticArray<double, Shape...>;

template <typename T, uint64_t Size> using StaticVector = StaticArray<T, Size>;

template <uint64_t Size> using StaticVectori = StaticVector<int, Size>;

template <uint64_t Size> using StaticVectorf = StaticVector<float, Size>;

template <uint64_t Size> using StaticVectord = StaticVector<double, Size>;

template <typename T, uint64_t M, uint64_t N>
using StaticMatrix = StaticArray<T, M, N>;

template <typename T, typename V = T, uint64_t... Shape>
constexpr StaticArray<V, Shape...>
empty_like(const StaticArray<T, Shape...> &array) {
  return StaticArray<V, Shape...>();
}

template <typename T, uint64_t Length>
constexpr bool all_equal(const StaticVector<T, Length> &left,
                         const StaticVector<T, Length> &right) {
  for (uint64_t index = 0; index < left.length(); ++index) {
    if (left(index) != right(index)) {
      return false;
    }
  }
  return true;
}

template <typename T, uint64_t Length1, uint64_t Length2, uint64_t... Lengths>
constexpr bool
all_equal(const StaticArray<T, Length1, Length2, Lengths...> &left,
          const StaticArray<T, Length1, Length2, Lengths...> &right) {
  for (uint64_t index = 0; index < left.length(); ++index) {
    if (!all_equal(left(index), right(index))) {
      return false;
    }
  }
  return true;
}

template <uint64_t Length>
constexpr bool all(const StaticVector<bool, Length> &vector) {
  for (uint64_t index = 0; index < vector.length(); ++index) {
    if (!vector(index)) {
      return false;
    }
  }
  return true;
}

template <uint64_t FirstLength, uint64_t SecondLength, uint64_t... Shape>
constexpr bool
all(const StaticArray<bool, FirstLength, SecondLength, Shape...> &array) {
  for (uint64_t index = 0; index < array.length(); ++index) {
    if (!all(array(index))) {
      return false;
    }
  }
  return true;
}

template <typename T, uint64_t N> constexpr StaticMatrix<T, N, N> Identity() {
  StaticMatrix<T, N, N> matrix;
  const T identity_element = static_cast<T>(1);
  const T zero_element = static_cast<T>(0);
  for (uint64_t row = 0; row < N; ++row) {
    for (uint64_t column = 0; column < N; ++column) {
      matrix(row, column) = (row == column ? identity_element : zero_element);
    }
  }
  return matrix;
}

template <uint64_t N> constexpr StaticVector<uint64_t, N> ARange() {
  StaticVector<uint64_t, N> range;
  for (uint64_t index = 0; index < N; ++index) {
    range(index) = index;
  }
  return range;
}
} // namespace sabai