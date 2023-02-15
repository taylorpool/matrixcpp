#include "sabai/string_representation.hpp"

#include <gtest/gtest.h>

TEST(HelloWorld, Hi) {
  sabai::StaticVectori<3> vector = {1, 2, 3};
  std::string answer = "3-element Vector<int>:\n1\n2\n3\n";
}