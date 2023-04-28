#include "sabai/sabai.hpp"

#include <gtest/gtest.h>

class VectorFixture : public ::testing::Test {
protected:
  int startingValue = 1;
  sabai::Vectori<1> x;

  VectorFixture() { x[0] = startingValue; }
};

TEST_F(VectorFixture, StartingValue) { ASSERT_EQ(x[0], startingValue); }

TEST_F(VectorFixture, PostIncrement) {
  int increment = 2;
  auto y = x + increment;
  ASSERT_EQ(y[0], x[0] + increment);
}

TEST_F(VectorFixture, PostDecrement) {
  int decrement = 2;
  auto y = x - decrement;
  ASSERT_EQ(y[0], x[0] - decrement);
}

TEST_F(VectorFixture, PostMultiply) {
  int multiple = 2;
  auto y = x * multiple;
  ASSERT_EQ(y[0], x[0] * multiple);
}

TEST_F(VectorFixture, PostDivide) {
  int divisor = -1;
  auto y = x / divisor;
  ASSERT_EQ(y[0], x[0] / divisor);
}

TEST_F(VectorFixture, PreIncrement) {
  int increment = 2;
  auto y = increment + x;
  ASSERT_EQ(y[0], increment + x[0]);
}

TEST_F(VectorFixture, PreDecrement) {
  int decrement = 2;
  auto y = decrement - x;
  ASSERT_EQ(y[0], decrement - x[0]);
}

TEST_F(VectorFixture, PreMultiply) {
  int multiple = 2;
  auto y = multiple * x;
  ASSERT_EQ(y[0], multiple * x[0]);
}

TEST_F(VectorFixture, PreDivide) {
  int dividend = 2;
  auto y = dividend / x;
  ASSERT_EQ(y[0], dividend / x[0]);
}

TEST_F(VectorFixture, PostAdditionToVector) {
  int increment = 2;
  decltype(x) y = x + increment;
  ASSERT_EQ(y[0], x[0] + increment);
}

TEST_F(VectorFixture, PreAdditionToVector) {
  int increment = 2;
  decltype(x) y = increment + x;
  ASSERT_EQ(y[0], increment + x[0]);
}
