#include "arithmetic/arithmetic.hpp"

#include <gtest/gtest.h>


TEST(Multiply, Multiply1)
{
        auto result = math::product(1);
        ASSERT_EQ(result, 1);
}

TEST(Multiply, Multiply2)
{
        auto result = math::product(1,2);
        ASSERT_EQ(result, 2);
}

TEST(Multiply, Multiply64)
{
        auto result = math::product(2,2,2,2,2,2);
        ASSERT_EQ(result, 64);
}