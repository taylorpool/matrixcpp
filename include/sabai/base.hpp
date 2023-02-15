#pragma once

#include <cstdint>
#include <exception>

namespace sabai {

template <typename T, typename U> struct is_same {
  static const bool value = false;
};

template <typename T> struct is_same<T, T> { static const bool value = true; };

template <typename T, bool IsStatic, uint64_t... Shape> class Array;

template <bool IsStatic, uint64_t... Shape>
using Arrayi = Array<int, IsStatic, Shape...>;

template <bool IsStatic, uint64_t... Shape>
using Arrayf = Array<float, IsStatic, Shape...>;

template <bool IsStatic, uint64_t... Shape>
using Arrayd = Array<double, IsStatic, Shape...>;

class OutOfRange : public std::exception {
private:
  uint64_t index_;
  uint64_t size_;

public:
  OutOfRange(uint64_t index, uint64_t size) : index_(index), size_(size){};

  ~OutOfRange() override{};

  const char *what() const noexcept override {
    return "index invalid for size";
  }
};
} // namespace sabai