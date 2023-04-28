#include "sabai/sabai.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  sabai::Vector<int, 3> x;
  static_assert(std::contiguous_iterator<sabai::Vector<int, 3>::iterator>);
  static_assert(std::ranges::contiguous_range<decltype(x)>);

  x[0] = -2;
  auto y = x + 1;
  std::cout << x[0] << std::endl;
  std::cout << y[0] << std::endl;

  x[0] = 0;

  std::cout << x[0] << std::endl;
  std::cout << y[0] << std::endl;

  return 0;
}