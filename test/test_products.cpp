#include "matrix/products.hpp"

#include "gtest/gtest.h"

TEST(DotProduct, VectorVector)
{
    math::Vectori<2> vector1 = {1,2};
    math::Vectori<2> vector2 = {3,4};
    auto result = math::dot(vector1, vector2);
    auto correct = vector1(0)*vector2(0)+vector1(1)*vector2(1);
    ASSERT_EQ(result, correct);
}

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