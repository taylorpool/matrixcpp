#include <gtest/gtest.h>

#include "matrix/operators.hpp"

class OperatorFixture: public ::testing::Test
{
    protected:
        math::Vectori<3> e1{{1, 0, 0}};
        math::Vectori<3> e2{{0, 1, 0}};
        math::Vectori<3> e3{{0, 0, 1}};
};

TEST_F(OperatorFixture, UnaryMinusE1)
{
    math::Vectori<3> negative_e1;
    for(int index = 0; index < 3; ++index)
    {
        negative_e1(index) = -e1(index);
    }
    ASSERT_EQ(-e1, negative_e1);
}

TEST_F(OperatorFixture, BinaryPlusE1E2)
{
    math::Vectori<3> my_sum = e1 + e2;
    math::Vectori<3> correct_sum;
    for(int index = 0; index < 3; ++index)
    {
        correct_sum(index) = e1(index) + e2(index);
    }
    ASSERT_EQ(my_sum, correct_sum);
}

TEST_F(OperatorFixture, BinaryPlusE1E2E3)
{
    math::Vectori<3> my_sum = e1 + e2 + e3;
    math::Vectori<3> correct_sum;
    for(int index = 0; index < 3; ++index)
    {
        correct_sum(index) = e1(index) + e2(index) + e3(index);
    }
    ASSERT_EQ(my_sum, correct_sum);
}

TEST_F(OperatorFixture, BinaryMinusE1E2)
{
    math::Vectori<3> my_difference = e1 - e2;
    math::Vectori<3> correct_difference;
    for(int index = 0; index < 3; ++index)
    {
        correct_difference(index) = e1(index) - e2(index);
    }
    ASSERT_EQ(my_difference, correct_difference);
}

TEST_F(OperatorFixture, BinaryMinusE1E2E3)
{
    math::Vectori<3> my_difference = e1 - e2 - e3;
    math::Vectori<3> correct_difference;
    for(int index = 0; index < 3; ++index)
    {
        correct_difference(index) = e1(index) - e2(index) - e3(index);
    }
    ASSERT_EQ(my_difference, correct_difference);
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