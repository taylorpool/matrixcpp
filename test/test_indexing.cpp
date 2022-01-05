#include "matrix/indexing.hpp"

#include <gtest/gtest.h>

class IndexingFixture: public ::testing::Test
{
    protected:
        math::Arrayi<2,2> A = {
            {1, 2},
            {3, 4}
        };
        math::Arrayi<3,3> matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        math::Vectori<5> vector = {
            0, 1, 2, 3, 4
        };
};

TEST_F(IndexingFixture, UpperTriangularA)
{
    math::Arrayi<2,2> B(A);
    B(1,0) = 0;
    ASSERT_EQ(B, math::triu(A));
}

TEST_F(IndexingFixture, UpperTriangularMatrix)
{
    math::Arrayi<3,3> upper_matrix(matrix);
    upper_matrix(1,0) = 0;
    upper_matrix(2,0) = 0;
    upper_matrix(2,1) = 0;
    ASSERT_EQ(upper_matrix, math::triu(matrix));
}

TEST_F(IndexingFixture, LowerTriangular)
{
    math::Arrayi<2,2> B(A);
    B(0,1) = 0;
    ASSERT_EQ(B, math::tril(A));
}

TEST_F(IndexingFixture, LowerTriangularMatrix)
{
    math::Arrayi<3,3> lower_matrix(matrix);
    lower_matrix(0,1) = 0;
    lower_matrix(0,2) = 0;
    lower_matrix(1,2) = 0;
    ASSERT_EQ(lower_matrix, math::tril(matrix));
}
TEST_F(IndexingFixture, SliceVector)
{
    auto vector_slice = math::slice<0,3>(vector);
    math::Vectori<3> answer = {
        0, 1, 2
    };
    ASSERT_EQ(vector_slice, answer);
}

TEST_F(IndexingFixture, SliceMatrix)
{
    auto matrix_slice = math::slice<0,2>(matrix);
    math::Arrayi<2,3> answer = {
        {matrix(0,0), matrix(0,1), matrix(0,2)},
        {matrix(1,0), matrix(1,1), matrix(1,2)}
    };
    ASSERT_EQ(matrix_slice, answer);
}