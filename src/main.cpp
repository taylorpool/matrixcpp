#include "sabai/sabai.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  sabai::Vector<int, 3> x;
  using X = decltype(x);

  static_assert(
      std::same_as<std::iter_reference_t<sabai::VectorIterator<int, 3>>,
                   int &>);
  static_assert(
      std::same_as<std::iter_reference_t<const sabai::VectorIterator<int, 3>>,
                   int &>);
  static_assert(
      std::same_as<std::remove_reference_t<sabai::VectorIterator<int, 3>>,
                   sabai::VectorIterator<int, 3>>);
  static_assert(
      std::same_as<std::remove_reference_t<sabai::VectorIterator<int, 3> &>,
                   sabai::VectorIterator<int, 3>>);

  static_assert(std::contiguous_iterator<sabai::VectorIterator<int, 3>>);
  static_assert(std::ranges::contiguous_range<decltype(x)>);

  auto y =
      x | std::ranges::views::transform([](int value) { return value + 1; });

  return 0;
}