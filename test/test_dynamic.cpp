#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class UninitializedDynamicVectorFixture: public ::testing::Test
{
    protected:
        math::DynamicVectori vectori;
        math::DynamicVectorf vectorf;
};

TEST_F(UninitializedDynamicVectorFixture, VectoriLength0)
{
    ASSERT_EQ(vectori.length(), 0);
}

TEST_F(UninitializedDynamicVectorFixture, VectoriOutOfRangeIndex)
{
    ASSERT_THROW(vectori(0), math::OutOfRange);
}

TEST_F(UninitializedDynamicVectorFixture, VectorfLength0)
{
    ASSERT_EQ(vectorf.length(), 0);
}

TEST_F(UninitializedDynamicVectorFixture, VectorfOutOfRangeIndex)
{
    ASSERT_THROW(vectorf(0), math::OutOfRange);
}

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

TEST_F(DynamicVectorFixture, FillBool)
{
    bool value = true;
    vectorb.fill(value);
    ASSERT_EQ(vectorb(0), value);
    ASSERT_EQ(vectorb(1), value);
}

TEST_F(DynamicVectorFixture, FillDouble)
{
    double value = 1.0;
    vectord.fill(value);
    ASSERT_EQ(vectord(0), value);
    ASSERT_EQ(vectord(1), value);
}
 
TEST_F(DynamicVectorFixture, FillFloat)
{
    float value = 1.0f;
    vectorf.fill(value);
    ASSERT_EQ(vectorf(0), value);
    ASSERT_EQ(vectorf(1), value);
}

TEST_F(DynamicVectorFixture, FillInt)
{
    int value = 1;
    vectori.fill(value);
    ASSERT_EQ(vectori(0), value);
    ASSERT_EQ(vectori(1), value);
}

TEST_F(DynamicVectorFixture, IntIndexOutOfRange)
{
    ASSERT_THROW(vectori(length), math::OutOfRange);
}

class DynamicMatrixFixture: public ::testing::Test
{
    protected:
        int length[2] = {2, 2};
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;

        math::DynamicArrayi<2> matrix;
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

TEST_F(DynamicMatrixFixture, Filla)
{
    matrix.fill(a);
    ASSERT_EQ(matrix(0,0), a);
    ASSERT_EQ(matrix(0,1), a);
    ASSERT_EQ(matrix(1,0), a);
    ASSERT_EQ(matrix(1,1), a);
}

TEST_F(DynamicMatrixFixture, FillFloat)
{
    float value = 3.14f;
    matrixf.fill(value);
    ASSERT_EQ(matrixf(0,0), value);
    ASSERT_EQ(matrixf(0,1), value);
    ASSERT_EQ(matrixf(1,0), value);
    ASSERT_EQ(matrixf(1,1), value);
}

TEST_F(DynamicMatrixFixture, FillDouble)
{
    double value = 3.14;
    matrixd.fill(value);
    ASSERT_EQ(matrixd(0,0), value);
    ASSERT_EQ(matrixd(0,1), value);
    ASSERT_EQ(matrixd(1,0), value);
    ASSERT_EQ(matrixd(1,1), value);
}

class DynamicTensorFixture: public ::testing::Test
{
    protected:
        int shape[3] = {2, 2, 2};
        math::DynamicArrayi<3> tensor;
        int a = 99;

        DynamicTensorFixture()
        : tensor(shape[0], shape[1], shape[2]) {};
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

TEST_F(DynamicTensorFixture, GetVectorSize)
{
    ASSERT_EQ(tensor(0,0).length(), shape[2]);
}

TEST_F(DynamicTensorFixture, SetElement)
{
    tensor(0,0,0) = a;
    ASSERT_EQ(tensor(0,0,0), a);
}