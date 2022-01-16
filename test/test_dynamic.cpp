#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class DynamicVectorFixture: public ::testing::Test
{
    protected:
        int size = 2;
        math::dynamic::Vectori vectori;
        math::dynamic::Vectorf vectorf;
        math::dynamic::Vectord vectord;
        math::dynamic::Vector<bool> vectorb;

        DynamicVectorFixture()
        : vectori(size),
          vectorf(size),
          vectord(size),
          vectorb(size) {};
};

TEST_F(DynamicVectorFixture, Size2TypeInt)
{
    ASSERT_EQ(vectori.size(), size);
}

TEST_F(DynamicVectorFixture, SetElementsTypeInt)
{
    int first_value = 1;
    vectori(0) = first_value;
    ASSERT_EQ(vectori(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeDouble)
{
    ASSERT_EQ(vectord.size(), size);
}

TEST_F(DynamicVectorFixture, SetElementsTypeDouble)
{
    double first_value = 1.0;
    vectord(0) = first_value;
    ASSERT_EQ(vectord(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeBool)
{
    ASSERT_EQ(vectorb.size(), size);
}

TEST_F(DynamicVectorFixture, SetElementsTypeBool)
{
    bool first_value = false;
    vectorb(0) = first_value;
    ASSERT_EQ(vectorb(0), first_value);
}

class DynamicMatrixFixture: public ::testing::Test
{
    protected:
        int size[2] = {2, 2};
        math::dynamic::Array<int, 2> matrix;
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;

        math::dynamic::Arrayd<2> matrixd;
        math::dynamic::Arrayf<2> matrixf;

        DynamicMatrixFixture()
        : matrix(size[0], size[1]),
          matrixd(size[0], size[1]),
          matrixf(size[0], size[1]) {}
};

TEST_F(DynamicMatrixFixture, GetSize)
{
    ASSERT_EQ(matrix.size(), size[0]);
}

TEST_F(DynamicMatrixFixture, GetRowSize)
{
    ASSERT_EQ(matrix(0).size(), size[1]);
}

TEST_F(DynamicMatrixFixture, SetElementa)
{
    matrix(0,0) = a;
    ASSERT_EQ(matrix(0,0), a);
}

TEST_F(DynamicMatrixFixture, SetElementb)
{
    matrix(0,1) = b;
    ASSERT_EQ(matrix(0,1), b);
}

TEST_F(DynamicMatrixFixture, SetElementc)
{
    matrix(1,0) = c;
    ASSERT_EQ(matrix(1,0), c);
}

TEST_F(DynamicMatrixFixture, SetElementd)
{
    matrix(1,1) = d;
    ASSERT_EQ(matrix(1,1), d);
}

class DynamicTensorFixture: public ::testing::Test
{
    protected:
        int shape[3] = {2, 2, 2};
        math::dynamic::Arrayi<3> tensor;
        int a = 99;

        math::dynamic::Arrayf<3> tensorf;
        math::dynamic::Arrayd<3> tensord;

        DynamicTensorFixture()
        : tensor(shape[0], shape[1], shape[2]),
          tensorf(shape[0], shape[1], shape[2]),
          tensord(shape[0], shape[1], shape[2]) {}
};

TEST_F(DynamicTensorFixture, GetSize)
{
    ASSERT_EQ(tensor.size(), shape[0]);
}

TEST_F(DynamicTensorFixture, GetMatrix0Size)
{
    ASSERT_EQ(tensor(0).size(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetMatrix1Size)
{
    ASSERT_EQ(tensor(1).size(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetMatrix2Size)
{
    ASSERT_EQ(tensor(2).size(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetVectorSize)
{
    ASSERT_EQ(tensor(0,0).size(), shape[2]);
}

TEST_F(DynamicTensorFixture, SetElement)
{
    tensor(0,0,0) = a;
    ASSERT_EQ(tensor(0,0,0), a);
}