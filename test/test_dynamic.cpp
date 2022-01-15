#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class DynamicVector: public ::testing::Test
{
    protected:
        int size = 2;
        math::dynamic::Vectori vectori;
        DynamicVector()
        : vectori(size) {};
};

TEST_F(DynamicVector, Size2)
{
    ASSERT_EQ(vectori.size(), size);
}

TEST_F(DynamicVector, SetElements)
{
    int first_value = 1;
    vectori(0) = first_value;
    ASSERT_EQ(vectori(0), first_value);
}