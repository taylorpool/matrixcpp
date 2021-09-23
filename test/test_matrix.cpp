#include "/home/taylor/math-matrix/include/matrix/matrix.hpp"
#include "gtest/gtest.h"

TEST(Matrix, Construct)
{
        auto singleton = math::Matrix<double, 1>();
        auto column_vector = math::Matrix<double, 2, 1>();
        auto matrix = math::Matrix<double, 2, 2>();
}

TEST(Matrixd, Construct)
{
        auto matrix = math::Matrixd<2, 2>();
}

TEST(Vector, AccessSingleValue)
{
        auto vector = math::Vector<double, 1>();
}

TEST(Vector, GetShape)
{
        auto vector = math::Vector<double, 1>();
        auto shape = vector.getShape();
        auto true_shape = std::array<int, 2>({1,1});
        ASSERT_EQ(shape, true_shape);
}