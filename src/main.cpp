#include "sabai/sabai.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  sabai::Vector<int, 3> x;

  static_assert(
      std::same_as<std::iter_reference_t<sabai::Vector<int, 3>::iterator>,
                   int &>);
  static_assert(
      std::same_as<std::iter_reference_t<const sabai::Vector<int, 3>::iterator>,
                   int &>);
  static_assert(
      std::same_as<std::remove_reference_t<sabai::Vector<int, 3>::iterator>,
                   sabai::Vector<int, 3>::iterator>);
  static_assert(
      std::same_as<std::remove_reference_t<sabai::Vector<int, 3>::iterator &>,
                   sabai::Vector<int, 3>::iterator>);

  static_assert(std::contiguous_iterator<sabai::Vector<int, 3>::iterator>);
  static_assert(std::ranges::contiguous_range<decltype(x)>);

  auto y =
      x | std::ranges::views::transform([](int value) { return value + 1; });

  x[0] = 0;
  std::cout << x[0] << std::endl;
  std::cout << y[0] << std::endl;

  return 0;
}