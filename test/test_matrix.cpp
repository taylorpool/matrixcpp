#include "matrix/matrix.hpp"
#include "gtest/gtest.h"

TEST(Matrix, Construct)
{
        auto singleton = math::Matrix<double, 1>(0.0);
        auto column_vector = math::Matrix<double, 2, 1>(0.0);
        auto matrix = math::Matrix<double, 2, 2>(0.0);
}

TEST(Matrixd, Construct)
{
        auto matrix = math::Matrixd<2, 2>(0.0);
}

TEST(Multiply, Multiply1)
{
        auto result = math::product(1);
        ASSERT_EQ(result, 1);
}

TEST(Multiply, Multiply2)
{
        auto result = math::product(1,2);
        ASSERT_EQ(result, 2);
}

TEST(Multiply, Multiply64)
{
        auto result = math::product(2,2,2,2,2,2);
        ASSERT_EQ(result, 64);
}

TEST(Vector, Zeros)
{
        auto vector = math::Vector<int, 3>(0);
        ASSERT_EQ(vector(0), 0);
}

TEST(Vector, Ones)
{
        auto vector = math::Vector<int, 3>(1);
        ASSERT_EQ(vector(0), 1);
}

TEST(Matrix, AccessElement)
{
        auto matrix = math::Matrix<double, 2, 2>(0.0);
        auto ans = math::Vector<double, 2>(0.0);
        ASSERT_EQ(matrix(0), ans);
}

TEST(Matrix, AccessElement2)
{
        auto matrix = math::Matrix<double, 2, 2>(0.0);
        auto ans = math::Vector<double, 2>(1.0);
        ASSERT_NE(matrix(0), ans);
}

TEST(Multiply, MatrixVector)
{
        auto matrix = math::Matrix<int, 2, 2>(1.0);
        auto vector = math::Vector<int, 2>(1.0);
        auto result = matrix*vector;
        ASSERT_EQ(result(0), 2.0);
}

TEST(Multiply, MatrixMatrix)
{
        auto A = math::Matrix<int, 2, 2>(1.0);
        auto B = math::Matrix<int, 2, 2>(1.0);
        auto result = A*B;
        auto answer = math::Matrix<int, 2, 2>(2.0);
        ASSERT_EQ(result, answer);
}

TEST(Matrix, CreateMatrix)
{
        auto A = math::Matrix<int, 2>({1, 2});
        ASSERT_EQ(A(0), 1);
        ASSERT_EQ(A(1), 2);
}

TEST(Matrix, CreateMatrix2)
{
        auto A = math::Matrix<int, 2, 2>({
                {1, 2},
                {3, 4}});
        ASSERT_EQ(A(0,0), 1);
        ASSERT_EQ(A(0,1), 2);
        ASSERT_EQ(A(1,0), 3);
        ASSERT_EQ(A(1,1), 4);
        math::Matrix<int, 2> first_row = {1,2};
        ASSERT_EQ(A(0), first_row);
}