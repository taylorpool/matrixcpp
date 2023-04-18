#pragma once
#include "sabai/base.hpp"

#include <initializer_list>

namespace sabai {

class MismatchedLength : public std::exception {
private:
  size_t left_length_;
  size_t right_length_;

public:
  MismatchedLength(size_t left_length, size_t right_length)
      : left_length_(left_length), right_length_(right_length) {}

  ~MismatchedLength() override{};

  const char *what() const noexcept override { return "mismatched lengths"; }
};

template <typename T, size_t... Shape> class DynamicArray;

template <typename T> class DynamicArray<T, 1> {
private:
  size_t length_;
  T *data_;

  void check_input(size_t index) const {
    if (index >= length_ || index < 0) {
      throw OutOfRange(index, length_);
    }
  }

  void check_length_matches(const DynamicArray &array) const {
    if (length_ != array.length()) {
      throw MismatchedLength(length_, array.length());
    }
  }

public:
  using InitializerList = std::initializer_list<T>;

  constexpr DynamicArray() : length_(static_cast<size_t>(0)) {}

  constexpr DynamicArray(size_t _length)
      : length_(_length), data_(new T[length_]) {}

  constexpr DynamicArray(const DynamicArray &array)
      : length_(array.length()), data_(new T[length_]) {
    fill(array);
  }

  constexpr DynamicArray(const InitializerList &values)
      : length_(values.size()), data_(new T[length_]) {
    size_t index = 0;
    for (const T &value : values) {
      data_[index] = value;
      ++index;
    }
  }

  constexpr void allocate(size_t _length) {
    if (length_ > static_cast<size_t>(0)) {
      delete[] data_;
    }
    data_ = new T[_length];
    length_ = _length;
  }

  constexpr void allocate_like(const DynamicArray &array) {
    allocate(array.length());
  }

  constexpr ~DynamicArray() {
    if (length_ > static_cast<size_t>(0)) {
      delete[] data_;
    }
  }

  constexpr T operator()(size_t index) const {
    check_input(index);
    return data_[index];
  }

  constexpr T &operator()(size_t index) {
    check_input(index);
    return data_[index];
  }

  constexpr size_t length() const { return length_; }

  constexpr void fill(const InitializerList &values) {
    if (length_ == static_cast<size_t>(0)) {
      allocate(values.size());
    }
    if (values.size() != length_) {
      throw MismatchedLength(length_, values.size());
    }
    size_t index = static_cast<size_t>(0);
    for (T value : values) {
      data_[index] = value;
      ++index;
    }
  }

  constexpr void fill(T value) {
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index] = value;
    }
  }

  constexpr void fill(const DynamicArray &vector) {
    if (length_ == static_cast<size_t>(0)) {
      allocate(vector.length());
    }
    check_length_matches(vector);
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index] = vector(index);
    }
  }

  constexpr void operator=(const DynamicArray &vector) {
    if (length_ == static_cast<size_t>(0)) {
      allocate(vector.length());
    }
    check_length_matches(vector);
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index] = vector(index);
    }
  }

  constexpr DynamicArray
  operator()(const DynamicArray<size_t, 1> &indices) const {
    DynamicArray indexed(indices.length());
    for (size_t index = static_cast<size_t>(0); index < indexed.length();
         ++index) {
      auto data = data_[indices(index)];
      indexed(index) = data;
    }
    return indexed;
  }
};

template <typename T, size_t NumDims>
requires(NumDims > static_cast<size_t>(1)) class DynamicArray<T, NumDims> {
public:
  using SubArray = DynamicArray<T, NumDims - 1>;

private:
  size_t length_;
  SubArray *data_;

  constexpr void check_input(size_t index) const {
    if (index >= length_) {
      throw OutOfRange(index, length_);
    }
  }

public:
  using InitializerList =
      std::initializer_list<typename SubArray::InitializerList>;

  constexpr DynamicArray() : length_(static_cast<size_t>(0)) {}

  template <typename... OtherDims>
  requires(sizeof...(OtherDims) ==
           (NumDims - 1)) constexpr DynamicArray(size_t _length,
                                                 OtherDims... others)
      : length_(_length), data_(new SubArray[length_]) {
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].allocate(others...);
    }
  }

  constexpr DynamicArray(const DynamicArray &array)
      : length_(array.length()), data_(new SubArray[length_]) {
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].fill(array(index));
    }
  }

  constexpr DynamicArray(const InitializerList &values)
      : length_(values.size()), data_(new SubArray[length_]) {
    size_t index = static_cast<size_t>(0);
    for (typename SubArray::InitializerList value : values) {
      data_[index].fill(value);
      ++index;
    }
  }

  constexpr ~DynamicArray() {
    if (length_ > static_cast<size_t>(0)) {
      delete[] data_;
    }
  }

  constexpr void fill(const DynamicArray &array) {
    if (length_ == static_cast<size_t>(0)) {
      allocate(array.length());
    } else if (length_ != array.length()) {
      throw MismatchedLength(length_, array.length());
    }
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].fill(array(index));
    }
  }

  constexpr SubArray operator()(size_t index) const {
    check_input(index);
    return data_[index];
  }

  constexpr SubArray &operator()(size_t index) {
    check_input(index);
    return data_[index];
  }

  template <typename... OtherIndices>
  requires(sizeof...(OtherIndices) > 0) constexpr auto
  operator()(size_t index, OtherIndices... others) const {
    check_input(index);
    return data_[index](others...);
  }

  template <typename... OtherIndices>
  requires(sizeof...(OtherIndices) > 0) constexpr auto &
  operator()(size_t index, OtherIndices... others) {
    check_input(index);
    return data_[index](others...);
  }

  constexpr size_t length() const { return length_; }

  constexpr void fill(T value) {
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].fill(value);
    }
  }

  constexpr void fill(const InitializerList &values) {
    if (length_ == static_cast<size_t>(0)) {
      allocate(values.size());
    }
    if (values.size() != length_) {
      throw MismatchedLength(length_, values.size());
    }
    size_t index = static_cast<size_t>(0);
    for (typename SubArray::InitializerList value : values) {
      data_[index].fill(value);
      ++index;
    }
  }

  constexpr void allocate(size_t _length) {
    if (length_ > static_cast<size_t>(0)) {
      delete[] data_;
    }
    data_ = new SubArray[_length];
    length_ = _length;
  }

  template <typename... OtherLengths>
  requires(sizeof...(OtherLengths) ==
           (NumDims - 1)) constexpr void allocate(size_t _length,
                                                  OtherLengths... others) {
    allocate(_length);
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].allocate(others...);
    }
  }

  constexpr void allocate_like(const DynamicArray &array) {
    allocate(array.length());
    for (size_t index = static_cast<size_t>(0); index < length_; ++index) {
      data_[index].allocate_like(array(index));
    }
  }

  constexpr void operator=(const DynamicArray &array) { fill(array); }

  constexpr DynamicArray
  operator()(const DynamicArray<size_t, 1> &indices) const {
    DynamicArray indexed;
    indexed.allocate(indices.length());
    for (size_t index = static_cast<size_t>(0); index < indices.length();
         ++index) {
      indexed(index) = data_[indices(index)];
    }
    return indexed;
  }
};

template <size_t NumDims> using DynamicArrayi = DynamicArray<int, NumDims>;

template <size_t NumDims> using DynamicArrayf = DynamicArray<float, NumDims>;

template <size_t NumDims> using DynamicArrayd = DynamicArray<double, NumDims>;

template <typename T> using DynamicVector = DynamicArray<T, 1>;

using DynamicVectori = DynamicVector<int>;

using DynamicVectorf = DynamicVector<float>;

using DynamicVectord = DynamicVector<double>;

template <typename T> using DynamicMatrix = DynamicArray<T, 2>;

using DynamicMatrixi = DynamicMatrix<int>;

using DynamicMatrixf = DynamicMatrix<float>;

using DynamicMatrixd = DynamicMatrix<double>;

template <typename T>
constexpr DynamicVector<T> empty_like(const DynamicVector<T> &vector) {
  DynamicVector<T> empty_vector(vector.length());
  return empty_vector;
};

template <typename T, size_t NumDims>
constexpr DynamicArray<T, NumDims>
empty_like(const DynamicArray<T, NumDims> &array) {
  DynamicArray<T, NumDims> empty_array;
  empty_array.allocate_like(array);
  return empty_array;
};

template <typename T>
constexpr bool all_equal(const DynamicVector<T> &left,
                         const DynamicVector<T> &right) {
  if (left.length() != right.length()) {
    throw MismatchedLength(left.length(), right.length());
  }

  for (size_t index = static_cast<size_t>(0); index < left.length(); ++index) {
    if (left(index) != right(index)) {
      return false;
    }
  }
  return true;
};

template <typename T, size_t NumDims>
constexpr bool all_equal(const DynamicArray<T, NumDims> &left,
                         const DynamicArray<T, NumDims> &right) {
  if (left.length() != right.length()) {
    throw MismatchedLength(left.length(), right.length());
  }

  for (size_t index = static_cast<size_t>(0); index < left.length(); ++index) {
    if (!all_equal(left(index), right(index))) {
      return false;
    }
  }
  return true;
};

template <typename T> constexpr DynamicMatrix<T> Identity(size_t N) {
  DynamicMatrix<T> matrix(N, N);
  const auto identity_element = static_cast<T>(1);
  const auto zero_element = static_cast<T>(0);
  for (size_t row = static_cast<size_t>(0); row < N; ++row) {
    for (size_t column = static_cast<size_t>(0); column < N; ++column) {
      matrix(row, column) = (row == column ? identity_element : zero_element);
    }
  }
  return matrix;
};

constexpr DynamicVector<size_t> ARange(size_t N) {
  DynamicVector<size_t> range(N);
  for (size_t index = static_cast<size_t>(0); index < N; ++index) {
    range(index) = index;
  }
  return range;
}

} // namespace sabai
