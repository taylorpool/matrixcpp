#include "sabai/sabai.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  sabai::Vector<int, 3> x;
  static_assert(std::contiguous_iterator<sabai::Vector<int, 3>::iterator>);
  static_assert(std::ranges::contiguous_range<decltype(x)>);

  auto y = x + 1;
  auto z = x - 1;
  auto a = 1 + x;
  auto b = 1 - x;
  auto c = x * 2;
  auto d = 2 * x;
  auto e = -x;
  auto f = x / 2;
  auto g = 2 / x;

  x[0] = -2;
  x[1] = -3;
  x[2] = -4;
  std::cout << "x: " << x[0] << std::endl;
  std::cout << "x + 1: " << y[0] << std::endl;
  std::cout << "x - 1: " << z[0] << std::endl;
  std::cout << "1 + x: " << a[0] << std::endl;
  std::cout << "1 - x: " << b[0] << std::endl;
  std::cout << "x * 2: " << c[0] << std::endl;
  std::cout << "2 * x: " << d[0] << std::endl;
  std::cout << "-x: " << e[0] << std::endl;
  std::cout << "x / 2: " << f[0] << std::endl;
  std::cout << "2 / x: " << g[0] << std::endl;

  std::cout << std::endl;

  x[0] = 2;
  x[1] = 3;
  x[2] = 4;
  std::cout << "x: " << x[0] << std::endl;
  std::cout << "x + 1: " << y[0] << std::endl;
  std::cout << "x - 1: " << z[0] << std::endl;
  std::cout << "1 + x: " << a[0] << std::endl;
  std::cout << "1 - x: " << b[0] << std::endl;
  std::cout << "x * 2: " << c[0] << std::endl;
  std::cout << "2 * x: " << d[0] << std::endl;
  std::cout << "-x: " << e[0] << std::endl;
  std::cout << "x / 2: " << f[0] << std::endl;
  std::cout << "2 / x: " << g[0] << std::endl;

  sabai::Vector<int, 3> vec_y = x + 1;

  static_assert(std::same_as<decltype(vec_y), decltype(x)>);

  std::cout << vec_y[0] << std::endl;
  std::cout << vec_y[1] << std::endl;
  std::cout << vec_y[2] << std::endl;

  return 0;
}