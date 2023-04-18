#pragma once

#include <cstdint>
#include <exception>

namespace sabai {

template <typename T, typename U> struct is_same {
  static const bool value = false;
};

template <typename T> struct is_same<T, T> { static const bool value = true; };

class OutOfRange : public std::exception {
private:
  size_t index_;
  size_t size_;

public:
  OutOfRange(size_t index, size_t size) : index_(index), size_(size){};

  ~OutOfRange() override{};

  const char *what() const noexcept override {
    return "index invalid for size";
  }
};
} // namespace sabai