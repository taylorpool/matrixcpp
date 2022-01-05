#include "matrix/products.hpp"

#include "gtest/gtest.h"

TEST(ScalarProduct, ScalarVector)
{
    math::Vectori<2> vector = {1,2};
    int factor = 10;
    decltype(vector) answer = {factor*vector(0), factor*vector(1)};
    ASSERT_EQ(factor*vector, answer);
}

TEST(ScalarProduct, VectorScalar)
{
    math::Vectori<2> vector = {1,2};
    int factor = 10;
    decltype(vector) answer = {factor*vector(0), factor*vector(1)};
    ASSERT_EQ(vector*factor, answer);
}

TEST(ScalarProduct, ScalarArray)
{
    math::Arrayi<2,2> matrix = {
        {1, 2},
        {3, 4}
    };
    int factor = 10;
    decltype(matrix) answer = {
        {factor*matrix(0,0), factor*matrix(0,1)},
        {factor*matrix(1,0), factor*matrix(1,1)}
    };
    ASSERT_EQ(factor*matrix, answer);
}

TEST(ScalarProduct, ArrayScalar)
{
    math::Arrayi<2,2> matrix = {
        {1, 2},
        {3, 4}
    };
    int factor = 10;
    decltype(matrix) answer = {
        {factor*matrix(0,0), factor*matrix(0,1)},
        {factor*matrix(1,0), factor*matrix(1,1)}
    };
    ASSERT_EQ(matrix*factor, answer);
}

class ProductFixture: public ::testing::Test
{
    protected:
        math::Vectori<3> e1{{1, 0, 0}};
        math::Vectori<3> e2{{0, 1, 0}};
        math::Vectori<3> e3{{0, 0, 1}};
};

TEST_F(ProductFixture, Orthogonal_DotProduct_0)
{
    auto result = math::dot(e1, e2);
    ASSERT_EQ(result, 0);
}

TEST_F(ProductFixture, SameUnitVector_DotProduct_1)
{
    auto result = math::dot(e1, e1);
    ASSERT_EQ(result, 1);
}

TEST_F(ProductFixture, E1CrossE2_E3)
{
    ASSERT_EQ(math::cross(e1, e2), e3);
}

TEST_F(ProductFixture, NegE2CrossE1_E3)
{
    ASSERT_EQ(math::cross(-e2, e1), e3);
}

TEST_F(ProductFixture, DistributiveCrossProduct)
{
    auto left = math::cross(e1, math::cross(e2,e3));
    auto right = math::dot(e1, e3)*e2 - math::dot(e1, e2)*e3;
    ASSERT_EQ(left, right);
}

TEST_F(ProductFixture, DistributiveDotOnCrossProduct1)
{
    auto result1 = math::dot(e1, math::cross(e2, e3));
    auto result2 = math::dot(e3, math::cross(e1, e2));
    ASSERT_EQ(result1, result2);
}

TEST_F(ProductFixture, DistributiveDotOnCrossProduct2)
{
    auto result2 = math::dot(e3, math::cross(e1, e2));
    auto result3 = math::dot(e2, math::cross(e3, e1));
    ASSERT_EQ(result2, result3);
}

TEST(Multiply, ArrayVector)
{
        auto matrix = math::Array<int, 2, 2>(1);
        auto vector = math::Vector<int, 2>(1);
        auto result = matrix*vector;
        math::Vectori<2> correct = {
            matrix(0,0)*vector(0)+matrix(0,1)*vector(1),
            matrix(1,0)*vector(0)+matrix(1,1)*vector(1)
        };
        ASSERT_EQ(result, correct);
}

TEST(Multiply, ArrayArray)
{
        auto A = math::Array<int, 2, 2>(1);
        auto B = math::Array<int, 2, 2>(1);
        auto result = A*B;
        math::Array<int, 2, 2> answer = {
            {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
            {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)},
        };
        ASSERT_EQ(result, answer);
}

TEST(OuterProduct, VectorVector)
{
    math::Vectori<2> vector1 = {1, 2};
    math::Vectori<2> vector2 = {3, 4};
    math::Arrayi<2,2> answer = {
        {vector1(0)*vector2(0), vector1(0)*vector2(1)},
        {vector1(1)*vector2(0), vector1(1)*vector2(1)}
    };
    ASSERT_EQ(math::outer(vector1, vector2), answer);
}