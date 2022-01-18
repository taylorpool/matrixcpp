#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class DynamicVectorFixture: public ::testing::Test
{
    protected:
        int length = 2;
        math::DynamicVectori vectori;
        math::DynamicVectorf vectorf;
        math::DynamicVectord vectord;
        math::DynamicVector<bool> vectorb;

        DynamicVectorFixture()
        : vectori(length),
          vectorf(length),
          vectord(length),
          vectorb(length) {};
};

TEST_F(DynamicVectorFixture, Size2TypeInt)
{
    ASSERT_EQ(vectori.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeInt)
{
    int first_value = 1;
    vectori(0) = first_value;
    ASSERT_EQ(vectori(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeDouble)
{
    ASSERT_EQ(vectord.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeDouble)
{
    double first_value = 1.0;
    vectord(0) = first_value;
    ASSERT_EQ(vectord(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeBool)
{
    ASSERT_EQ(vectorb.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeBool)
{
    bool first_value = false;
    vectorb(0) = first_value;
    ASSERT_EQ(vectorb(0), first_value);
}

TEST_F(DynamicVectorFixture, GetShape)
{

}

class DynamicMatrixFixture: public ::testing::Test
{
    protected:
        int length[2] = {2, 2};
        math::DynamicArray<int, 2> matrix;
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;

        math::DynamicArrayd<2> matrixd;
        math::DynamicArrayf<2> matrixf;

        DynamicMatrixFixture()
        : matrix(length[0], length[1]),
          matrixd(length[0], length[1]),
          matrixf(length[0], length[1]) {}
};

TEST_F(DynamicMatrixFixture, GetSize)
{
    ASSERT_EQ(matrix.length(), length[0]);
}

TEST_F(DynamicMatrixFixture, GetRowSize)
{
    ASSERT_EQ(matrix(0).length(), length[1]);
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
        math::DynamicArrayi<3> tensor;
        int a = 99;

        math::DynamicArrayf<3> tensorf;
        math::DynamicArrayd<3> tensord;

        DynamicTensorFixture()
        : tensor(shape[0], shape[1], shape[2]),
          tensorf(shape[0], shape[1], shape[2]),
          tensord(shape[0], shape[1], shape[2]) {}
};

TEST_F(DynamicTensorFixture, GetSize)
{
    ASSERT_EQ(tensor.length(), shape[0]);
}

TEST_F(DynamicTensorFixture, GetMatrix0Size)
{
    ASSERT_EQ(tensor(0).length(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetMatrix1Size)
{
    ASSERT_EQ(tensor(1).length(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetMatrix2Size)
{
    ASSERT_EQ(tensor(2).length(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetVectorSize)
{
    ASSERT_EQ(tensor(0,0).length(), shape[2]);
}

TEST_F(DynamicTensorFixture, SetElement)
{
    tensor(0,0,0) = a;
    ASSERT_EQ(tensor(0,0,0), a);
}