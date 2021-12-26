#include "matrix/products.hpp"

#include "gtest/gtest.h"

TEST(Multiply, MatrixVector)
{
        auto matrix = math::Matrix<int, 2, 2>(1.0);
        auto vector = math::Vector<int, 2>(1.0);
        auto result = matrix*vector;
        ASSERT_EQ(result(0), 2.0);
}

TEST(Multiply, MatrixMatrix)
{
        auto A = math::Matrix<int, 2, 2>(1.0);
        auto B = math::Matrix<int, 2, 2>(1.0);
        auto result = A*B;
        auto answer = math::Matrix<int, 2, 2>(2.0);
        ASSERT_EQ(result, answer);
}