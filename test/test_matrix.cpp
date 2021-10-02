#include "matrix/matrix.hpp"
#include "gtest/gtest.h"

TEST(Matrix, Construct)
{
        auto singleton = math::Matrix<double, 1>(0.0);
        auto column_vector = math::Matrix<double, 2, 1>(0.0);
        auto matrix = math::Matrix<double, 2, 2>(0.0);
}

TEST(Matrixd, Construct)
{
        auto matrix = math::Matrixd<2, 2>(0.0);
}

TEST(Matrix, GetDimension)
{
        auto vector = math::Vector<double, 1>(0.0);
        auto dim = vector.getDimension();
        ASSERT_EQ(dim, 1);
}

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

TEST(Vector, GetSize)
{
        int desired_size = 10;
        auto vector = math::Vector<double, 10>(0.0);
        ASSERT_EQ(desired_size, vector.getSize());
}

TEST(Matrix, GetSize)
{
        auto matrix = math::Matrix<int, 10, 10, 10>(0.0);
        ASSERT_EQ(1000, matrix.getSize());
}

TEST(Vector, Zeros)
{
        auto vector = math::Vector<int, 3>(0);
        ASSERT_EQ(vector(0), 0);
}