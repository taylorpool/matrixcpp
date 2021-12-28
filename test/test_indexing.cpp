#include "matrix/indexing.hpp"

#include <gtest/gtest.h>

class IndexingFixture: public ::testing::Test
{
    protected:
        math::Arrayi<2,2> A = {
            {1, 2},
            {3, 4}
        };
};

TEST_F(IndexingFixture, UpperTriangular)
{
    math::Arrayi<2,2> A = {
        {1, 2},
        {3, 4}
    };
    
    auto B = A;
    B(1,0) = 0;

    ASSERT_EQ(B, math::triu(A));
}

TEST_F(IndexingFixture, LowerTriangular)
{
    math::Arrayi<2,2> A = {
        {1, 2},
        {3, 4}
    };
    
    auto B = A;
    B(0,1) = 0;

    ASSERT_EQ(B, math::tril(A));
}
