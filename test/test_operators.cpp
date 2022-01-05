#include <gtest/gtest.h>

#include "matrix/operators.hpp"

TEST(UnaryMinus, Vector)
{
    math::Vectori<3> vector = {1, 1, 1};
    math::Vectori<3> negative_vector;
    for(int index = 0; index < 3; ++index)
    {
        negative_vector(index) = -vector(index);
    }
    ASSERT_EQ(-vector, negative_vector);
}

TEST(UnaryMinus, Matrix)
{
    math::Arrayi<2,2> matrix = {
        {1, 2},
        {3, 4}
    };
    math::Arrayi<2,2> negative_matrix;
    for(int row = 0; row < 2; ++row)
    {
        for(int column = 0; column < 2; ++column)
        {
            negative_matrix(row,column) = -matrix(row,column);
        }
    }
    ASSERT_EQ(-matrix, negative_matrix);
}