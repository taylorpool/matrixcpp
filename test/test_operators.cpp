#include <gtest/gtest.h>

#include "matrix/static.hpp"
#include "matrix/dynamic.hpp"
#include "matrix/operators.hpp"

class StaticOperatorFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<3> e1{{1, 0, 0}};
        math::StaticVectori<3> e2{{0, 1, 0}};
        math::StaticVectori<3> e3{{0, 0, 1}};
        math::StaticArrayi<3,3> matrixi1{{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }};
        math::StaticArrayi<3,3> matrixi2{{
            {10, 11, 12},
            {13, 14, 15},
            {16, 17, 18}
        }};
        math::StaticArrayi<3,3> matrixi3{{
            {19, 20, 21},
            {22, 23, 24},
            {25, 26, 27}
        }};
};

TEST_F(StaticOperatorFixture, E1EqualsE1)
{
    math::Vector<bool,3> result = (e1 == e1);
}

TEST_F(StaticOperatorFixture, UnaryMinusMatrix2)
{
    math::StaticArrayi<3,3> negative_matrixi2;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            negative_matrixi2(row, col) = -matrixi2(row, col);
        }
    }
    ASSERT_EQ(negative_matrixi2, -matrixi2);
}

TEST_F(StaticOperatorFixture, UnaryMinusMatrix1)
{
    math::StaticArrayi<3,3> negative_matrixi1;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            negative_matrixi1(row, col) = -matrixi1(row, col);
        }
    }
    ASSERT_EQ(negative_matrixi1, -matrixi1);
}

TEST_F(StaticOperatorFixture, UnaryMinusE1)
{
    math::StaticVectori<3> negative_e1;
    for(int index = 0; index < 3; ++index)
    {
        negative_e1(index) = -e1(index);
    }
    ASSERT_EQ(-e1, negative_e1);
}

TEST_F(StaticOperatorFixture, BinaryPlusMatrix1Matrix2)
{
    math::StaticArrayi<3,3> matrix_sum = matrixi1 + matrixi2;
    math::StaticArrayi<3,3> correct_sum;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            correct_sum(row,col) = matrixi1(row,col)+matrixi2(row,col);
        }
    }
    ASSERT_EQ(matrix_sum, correct_sum);
}

TEST_F(StaticOperatorFixture, BinaryPlusMatrix1Matrix2Matrix3)
{
    math::StaticArrayi<3,3> matrix_sum = matrixi1 + matrixi2 + matrixi3;
    math::StaticArrayi<3,3> correct_sum;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            correct_sum(row,col) = matrixi1(row,col)
                + matrixi2(row,col)
                + matrixi3(row,col);
        }
    }
    ASSERT_EQ(matrix_sum, correct_sum);
}

TEST_F(StaticOperatorFixture, BinaryPlusE1E2)
{
    math::StaticVectori<3> my_sum = e1 + e2;
    math::StaticVectori<3> correct_sum;
    for(int index = 0; index < 3; ++index)
    {
        correct_sum(index) = e1(index) + e2(index);
    }
    ASSERT_EQ(my_sum, correct_sum);
}

TEST_F(StaticOperatorFixture, BinaryPlusE1E2E3)
{
    math::StaticVectori<3> my_sum = e1 + e2 + e3;
    math::StaticVectori<3> correct_sum;
    for(int index = 0; index < 3; ++index)
    {
        correct_sum(index) = e1(index) + e2(index) + e3(index);
    }
    ASSERT_EQ(my_sum, correct_sum);
}

TEST_F(StaticOperatorFixture, BinaryMinusMatrix1Matrix2)
{
    math::StaticArrayi<3,3> matrix_diff = matrixi1 - matrixi2;
    math::StaticArrayi<3,3> correct_diff;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            correct_diff(row,col) = matrixi1(row,col) - matrixi2(row,col);
        }
    }
    ASSERT_EQ(matrix_diff, correct_diff);
}

TEST_F(StaticOperatorFixture, BinaryMinusMatrix1Matrix2Matrix3)
{
    math::StaticArrayi<3,3> matrix_diff = matrixi1 - matrixi2 - matrixi3;
    math::StaticArrayi<3,3> correct_diff;
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            correct_diff(row,col) = matrixi1(row,col) 
                - matrixi2(row,col)
                - matrixi3(row,col);
        }
    }
    ASSERT_EQ(matrix_diff, correct_diff);
}

TEST_F(StaticOperatorFixture, BinaryMinusE1E2)
{
    math::StaticVectori<3> my_difference = e1 - e2;
    math::StaticVectori<3> correct_difference;
    for(int index = 0; index < 3; ++index)
    {
        correct_difference(index) = e1(index) - e2(index);
    }
    ASSERT_EQ(my_difference, correct_difference);
}

TEST_F(StaticOperatorFixture, BinaryMinusE1E2E3)
{
    math::StaticVectori<3> my_difference = e1 - e2 - e3;
    math::StaticVectori<3> correct_difference;
    for(int index = 0; index < 3; ++index)
    {
        correct_difference(index) = e1(index) - e2(index) - e3(index);
    }
    ASSERT_EQ(my_difference, correct_difference);
}

class DynamicOperatorFixture: public ::testing::Test
{
    protected:
        int length = 3;
        math::DynamicVectori vectori{(length)};
        math::DynamicVectori vectori2{(length)};
        
        DynamicOperatorFixture()
        {
            vectori(0) = 0;
            vectori(1) = 1;
            vectori(2) = 2;

            vectori2(0) = 0;
            vectori2(1) = 1;
            vectori2(2) = 2;
        }
};

TEST_F(DynamicOperatorFixture, UnaryMinus)
{
    math::DynamicVectori answer(vectori.length());
    for(int index = 0; index < answer.length(); ++index)
    {
        answer(index) = -vectori(index);
    }
    ASSERT_EQ(-vectori, answer);
}

TEST_F(DynamicOperatorFixture, BinaryPlus)
{
    math::DynamicVectori answer(length);
    for(int index = 0; index < answer.length(); ++index)
    {
        answer(index) = vectori(index)+vectori2(index);
    }
    ASSERT_EQ(vectori+vectori2, answer);
}

TEST_F(DynamicOperatorFixture, BinaryMinus)
{
    math::DynamicVectori answer(length);
    for(int index = 0; index < answer.length(); ++index)
    {
        answer(index) = vectori(index)-vectori2(index);
    }
    ASSERT_EQ(vectori-vectori2, answer);
}

TEST(UnaryMinus, Matrix)
{
    math::StaticArrayi<2,2> matrix = {
        {1, 2},
        {3, 4}
    };
    math::StaticArrayi<2,2> negative_matrix;
    for(int row = 0; row < 2; ++row)
    {
        for(int column = 0; column < 2; ++column)
        {
            negative_matrix(row,column) = -matrix(row,column);
        }
    }
    ASSERT_EQ(-matrix, negative_matrix);
}