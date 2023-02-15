#include "arithmetic/arithmetic.hpp"

#include <gtest/gtest.h>

TEST(ADD, Add1) {
  auto result = sabai::sum(1);
  ASSERT_EQ(result, 1);
}

TEST(ADD, Add2) {
  auto result = sabai::sum(1, 2);
  ASSERT_EQ(result, 3);
}

TEST(ADD, Add10) {
  auto result = sabai::sum(1, -1, 5, 5);
  ASSERT_EQ(result, 10);
}

TEST(ADD, AddFloat) {
  float values[] = {10.5f, -3.0f, 2.0f};
  float result = sabai::sum(values[0], values[1], values[2]);
  ASSERT_FLOAT_EQ(result, values[0] + values[1] + values[2]);
}

TEST(Multiply, Multiply1) {
  auto result = sabai::product(1);
  ASSERT_EQ(result, 1);
}

TEST(Multiply, Multiply2) {
  auto result = sabai::product(1, 2);
  ASSERT_EQ(result, 2);
}

TEST(Multiply, Multiply64) {
  auto result = sabai::product(2, 2, 2, 2, 2, 2);
  ASSERT_EQ(result, 64);
}