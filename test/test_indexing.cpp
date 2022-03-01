#include "matrix/indexing.hpp"
#include "matrix/operators.hpp"

#include <gtest/gtest.h>

class StaticIndexingFixture: public ::testing::Test
{
    protected:
        math::StaticArrayi<2,2> A = {
            {1, 2},
            {3, 4}
        };
        math::StaticArrayi<3,3> matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        math::StaticVectori<5> vector = {
            0, 1, 2, 3, 4
        };
};

TEST_F(StaticIndexingFixture, UpperTriangularA)
{
    math::StaticArrayi<2,2> B(A);
    B(1,0) = 0;
    ASSERT_TRUE(math::all_equal(B, math::triu(A)));
}

TEST_F(StaticIndexingFixture, UpperTriangularMatrix)
{
    math::StaticArrayi<3,3> upper_matrix(matrix);
    upper_matrix(1,0) = 0;
    upper_matrix(2,0) = 0;
    upper_matrix(2,1) = 0;
    ASSERT_TRUE(math::all_equal(upper_matrix, math::triu(matrix)));
}

TEST_F(StaticIndexingFixture, LowerTriangular)
{
    math::StaticArrayi<2,2> B(A);
    B(0,1) = 0;
    ASSERT_TRUE(math::all_equal(B, math::tril(A)));
}

TEST_F(StaticIndexingFixture, LowerTriangularMatrix)
{
    math::StaticArrayi<3,3> lower_matrix(matrix);
    lower_matrix(0,1) = 0;
    lower_matrix(0,2) = 0;
    lower_matrix(1,2) = 0;
    ASSERT_TRUE(math::all_equal(lower_matrix, math::tril(matrix)));
}
TEST_F(StaticIndexingFixture, SliceVector)
{
    auto vector_slice = math::slice<0,3>(vector);
    math::StaticVectori<3> answer = {
        0, 1, 2
    };
    ASSERT_TRUE(math::all_equal(vector_slice, answer));
}

TEST_F(StaticIndexingFixture, SliceMatrix)
{
    auto matrix_slice = math::slice<0,2>(matrix);
    math::StaticArrayi<2,3> answer = {
        {matrix(0,0), matrix(0,1), matrix(0,2)},
        {matrix(1,0), matrix(1,1), matrix(1,2)}
    };
    ASSERT_TRUE(math::all_equal(matrix_slice, answer));
}

class DynamicIndexingFixture: public ::testing::Test
{
    protected:
        math::DynamicMatrixi A = {
            {1, 2},
            {3, 4}
        };
        math::DynamicMatrixi matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        math::DynamicVectori vector = {
            0, 1, 2, 3, 4
        };
};

TEST_F(DynamicIndexingFixture, UpperTriangularA)
{
    math::DynamicMatrixi B(A);
    B(1,0) = 0;
    ASSERT_TRUE(math::all_equal(B, math::triu(A)));
}

TEST_F(DynamicIndexingFixture, UpperTriangularMatrix)
{
    math::DynamicMatrixi upper_matrix(matrix);
    upper_matrix(1,0) = 0;
    upper_matrix(2,0) = 0;
    upper_matrix(2,1) = 0;
    ASSERT_TRUE(math::all_equal(upper_matrix, math::triu(matrix)));
}

TEST_F(DynamicIndexingFixture, LowerTriangular)
{
    math::DynamicMatrixi B(A);
    B(0,1) = 0;
    ASSERT_TRUE(math::all_equal(B, math::tril(A)));
}

TEST_F(DynamicIndexingFixture, LowerTriangularMatrix)
{
    math::DynamicMatrixi lower_matrix(matrix);
    lower_matrix(0,1) = 0;
    lower_matrix(0,2) = 0;
    lower_matrix(1,2) = 0;
    ASSERT_TRUE(math::all_equal(lower_matrix, math::tril(matrix)));
}