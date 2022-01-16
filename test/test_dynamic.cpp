#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class DynamicVector: public ::testing::Test
{
    protected:
        int size = 2;
        math::dynamic::Vectori vectori;
        math::dynamic::Vectord vectord;
        math::dynamic::Vector<bool> vectorb;

        DynamicVector()
        : vectori(size), vectord(size),
          vectorb(size) {};
};

TEST_F(DynamicVector, Size2TypeInt)
{
    ASSERT_EQ(vectori.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeInt)
{
    int first_value = 1;
    vectori(0) = first_value;
    ASSERT_EQ(vectori(0), first_value);
}

TEST_F(DynamicVector, Size2TypeDouble)
{
    ASSERT_EQ(vectord.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeDouble)
{
    double first_value = 1.0;
    vectord(0) = first_value;
    ASSERT_EQ(vectord(0), first_value);
}

TEST_F(DynamicVector, Size2TypeBool)
{
    ASSERT_EQ(vectorb.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeBool)
{
    bool first_value = false;
    vectorb(0) = first_value;
    ASSERT_EQ(vectorb(0), first_value);
}

class DynamicMatrix: public ::testing::Test
{
    protected:
        int size[2] = {2, 2};
        math::dynamic::Array<int, 2> matrix;
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;

        DynamicMatrix()
        : matrix(size[0], size[1]) {}
};

TEST_F(DynamicMatrix, GetSize)
{
    ASSERT_EQ(matrix.size(), size[0]);
}

TEST_F(DynamicMatrix, GetRowSize)
{
    ASSERT_EQ(matrix(0).size(), size[1]);
}

TEST_F(DynamicMatrix, SetElementa)
{
    matrix(0,0) = a;
    ASSERT_EQ(matrix(0,0), a);
}

TEST_F(DynamicMatrix, SetElementb)
{
    matrix(0,1) = b;
    ASSERT_EQ(matrix(0,1), b);
}

TEST_F(DynamicMatrix, SetElementc)
{
    matrix(1,0) = c;
    ASSERT_EQ(matrix(1,0), c);
}

TEST_F(DynamicMatrix, SetElementd)
{
    matrix(1,1) = d;
    ASSERT_EQ(matrix(1,1), d);
}