#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

TEST(DynamicVector, Size2)
{
    int size = 2;
    math::dynamic::Vectori vector(size);
    ASSERT_EQ(vector.get_size(), size);
}