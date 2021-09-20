#include "/home/taylor/math-matrix/include/matrix/matrix.hpp"
#include "gtest/gtest.h"

class MatrixFixture: public ::testing::Test
{
protected:
        MatrixFixture():
        value{0.1},
        vector{{value}}
        {
        };
        double value;
        math::Matrix<double> vector;
};

TEST_F(MatrixFixture, AccessElement)
{
        ASSERT_DOUBLE_EQ(vector[0], value);
}

TEST_F(MatrixFixture, AssignElement)
{
        double new_value = 0.0;
        vector[0] = new_value;
        ASSERT_DOUBLE_EQ(vector[0], new_value);
}

TEST_F(MatrixFixture, GetSize)
{
        auto size = vector.getSize(); 
        ASSERT_EQ(size, 1);
}

TEST_F(MatrixFixture, GetShape)
{
        auto shape = vector.getShape(); 
        ASSERT_EQ(shape, std::vector<int>({1}));
}