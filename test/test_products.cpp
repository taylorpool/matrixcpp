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
        auto matrix = math::Matrix<int, 2, 2>(1);
        auto vector = math::Vector<int, 2>(1);
        auto result = matrix*vector;
        math::Vectori<2> correct = {
            matrix(0,0)*vector(0)+matrix(0,1)*vector(1),
            matrix(1,0)*vector(0)+matrix(1,1)*vector(1)
        };
        ASSERT_EQ(result, correct);
}

TEST(Multiply, MatrixMatrix)
{
        auto A = math::Matrix<int, 2, 2>(1.0);
        auto B = math::Matrix<int, 2, 2>(1.0);
        auto result = A*B;
        math::Matrix<int, 2, 2> answer = {
            {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
            {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)},
        };
        ASSERT_EQ(result, answer);
}