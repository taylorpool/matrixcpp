#include "matrix/base.hpp"

#include "gtest/gtest.h"

TEST(ZeroArray, Vector)
{
        int initial_value = 0;
        math::Vectori<2> vector(0);
        ASSERT_EQ(vector(0), initial_value);
        ASSERT_EQ(vector(1), initial_value);

}

TEST(ZeroArray, Matrix)
{
        int initial_value = 0;
        math::Arrayi<2,2> matrix(0);
        ASSERT_EQ(matrix(0,0), initial_value);
        ASSERT_EQ(matrix(0,1), initial_value);
        ASSERT_EQ(matrix(1,0), initial_value);
        ASSERT_EQ(matrix(1,1), initial_value);
}

TEST(Vector, Ones)
{
        auto vector = math::Vector<int, 3>(1);
        ASSERT_EQ(vector(0), 1);
        ASSERT_EQ(vector(1), 1);
        ASSERT_EQ(vector(2), 1);
}

class ZeroMatricies: public ::testing::Test
{
        protected:
                math::Vectori<2> vector{math::Vectori<2>(0)};
                math::Arrayi<2,2> matrix{math::Arrayi<2,2>(0)};
};

TEST_F(ZeroMatricies, Zeros)
{
        ASSERT_EQ(vector(0), 0);
        ASSERT_EQ(vector(1), 0);
}

TEST_F(ZeroMatricies, AccessElement)
{
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(ZeroMatricies, AccessElement2)
{
        auto ans = math::Vectori<2>(1.0);
        ASSERT_NE(matrix(0), ans);
}

class MultiDimensional: public ::testing::Test
{
        protected:
                math::Vectori<2> vector{{1, 2}};
                math::Arrayi<2, 2> matrix{{
                        {1, 2},
                        {3, 4}
                }};
                math::Arrayi<2, 2, 2> tensor{{
                        {
                                {1, 2},
                                {3, 4}
                        },
                        {
                                {5, 6},
                                {7, 8}
                        }
                }};
};

TEST_F(MultiDimensional, CreateVector)
{
        ASSERT_EQ(vector(0), 1);
        ASSERT_EQ(vector(1), 2);
}

TEST_F(MultiDimensional, CreateArray)
{
        ASSERT_EQ(matrix(0,0), 1);
        ASSERT_EQ(matrix(0,1), 2);
        ASSERT_EQ(matrix(1,0), 3);
        ASSERT_EQ(matrix(1,1), 4);
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(MultiDimensional, AssignElement)
{
        matrix(0,0) = 6;
        ASSERT_EQ(matrix(0,0), 6);
}

TEST_F(MultiDimensional, AssignTensorElement)
{
        tensor(0,0,0) = 0;
        ASSERT_EQ(tensor(0,0,0), 0);
}

TEST_F(MultiDimensional, GetFirstTensorArray)
{
        ASSERT_EQ(tensor(0), matrix);
}

TEST_F(MultiDimensional, GetFirstTensorVector)
{
        ASSERT_EQ(tensor(0,0), vector);
}

TEST_F(MultiDimensional, SetFirstTensorVector)
{
        math::Vectori<2> new_vector = {{100, 101}};
        ASSERT_NE(tensor(0,0), new_vector);
        tensor(0,0) = new_vector;
        ASSERT_EQ(tensor(0,0), new_vector);
}

TEST_F(MultiDimensional, MatrixIncrement)
{
        matrix(0,0) += 1;
        ASSERT_EQ(matrix(0,0), 2);
}

TEST(Identity, Matrix)
{
        auto matrix = math::Identity<int, 2>();
        decltype(matrix) answer = {
                {1, 0},
                {0, 1}
        };
        ASSERT_EQ(matrix, answer);
}

TEST(ARange, Vector)
{
        auto range = math::ARange<4>();
        math::Vectori<4> answer = {
                0, 1, 2, 3
        };
        ASSERT_EQ(range, answer);
}

TEST_F(MultiDimensional, IndexingVector)
{
        math::Vectori<1> indices = {1};
        math::Vectori<1> answer = {vector(indices(0))};
        ASSERT_EQ(answer, vector(indices));
}

TEST_F(MultiDimensional, IndexingMatrix)
{
        math::Vectori<1> indices = {1};
        math::Arrayi<1,2> answer = {
                {3, 4}
        };
        ASSERT_EQ(answer, matrix(indices));
}