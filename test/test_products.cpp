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
TEST(DotProduct, VectorVector)
{
    math::Vectori<2> vector1 = {1,2};
    math::Vectori<2> vector2 = {3,4};
    auto result = math::dot(vector1, vector2);
    auto correct = vector1(0)*vector2(0)+vector1(1)*vector2(1);
    ASSERT_EQ(result, correct);
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
        auto A = math::Array<int, 2, 2>(1.0);
        auto B = math::Array<int, 2, 2>(1.0);
        auto result = A*B;
        math::Array<int, 2, 2> answer = {
            {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
            {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)},
        };
        ASSERT_EQ(result, answer);
}