#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class InitializerListDynamicVector : public ::testing::Test {
protected:
  int values[5] = {1, 2, 3, 4, 5};
  sabai::DynamicVectori vectori{
      {values[0], values[1], values[2], values[3], values[4]}};
};

TEST_F(InitializerListDynamicVector, Size) { ASSERT_EQ(vectori.length(), 5); }

TEST_F(InitializerListDynamicVector, Value0) {
  ASSERT_EQ(vectori(0), values[0]);
}

TEST_F(InitializerListDynamicVector, Value1) {
  ASSERT_EQ(vectori(1), values[1]);
}

TEST_F(InitializerListDynamicVector, Value2) {
  ASSERT_EQ(vectori(2), values[2]);
}

TEST_F(InitializerListDynamicVector, Value3) {
  ASSERT_EQ(vectori(3), values[3]);
}

TEST_F(InitializerListDynamicVector, Value4) {
  ASSERT_EQ(vectori(4), values[4]);
}

class InitializerListDynamicMatrix : public ::testing::Test {
protected:
  int values[4] = {1, 2, 3, 4};
  sabai::DynamicArrayi<2> matrix{
      {{values[0], values[1]}, {values[2], values[3]}}};
};

TEST_F(InitializerListDynamicMatrix, CorrectSize) {
  ASSERT_EQ(matrix.length(), 2);
}

TEST_F(InitializerListDynamicMatrix, Element00) {
  ASSERT_EQ(matrix(0, 0), values[0]);
}

TEST_F(InitializerListDynamicMatrix, Element01) {
  ASSERT_EQ(matrix(0, 1), values[1]);
}

TEST_F(InitializerListDynamicMatrix, Element10) {
  ASSERT_EQ(matrix(1, 0), values[2]);
}

TEST_F(InitializerListDynamicMatrix, Element11) {
  ASSERT_EQ(matrix(1, 1), values[3]);
}

class UninitializedDynamicVectorFixture : public ::testing::Test {
protected:
  sabai::DynamicVectori vectori;
  sabai::DynamicVectorf vectorf;
};

TEST_F(UninitializedDynamicVectorFixture, VectoriLength0) {
  ASSERT_EQ(vectori.length(), 0);
}

TEST_F(UninitializedDynamicVectorFixture, VectoriOutOfRangeIndex) {
  ASSERT_THROW(vectori(0), sabai::OutOfRange);
}

TEST_F(UninitializedDynamicVectorFixture, VectorfLength0) {
  ASSERT_EQ(vectorf.length(), 0);
}

TEST_F(UninitializedDynamicVectorFixture, VectorfOutOfRangeIndex) {
  ASSERT_THROW(vectorf(0), sabai::OutOfRange);
}

class DynamicVectorFixture : public ::testing::Test {
protected:
  int length = 2;
  sabai::DynamicVectori vectori;
  sabai::DynamicVectorf vectorf;
  sabai::DynamicVectord vectord;
  sabai::DynamicVector<bool> vectorb;

  DynamicVectorFixture()
      : vectori(length), vectorf(length), vectord(length), vectorb(length){};
};

TEST_F(DynamicVectorFixture, FillElementsBool) {
  bool a = false;
  bool b = true;
  vectorb.fill({a, b});
  ASSERT_EQ(vectorb(0), a);
  ASSERT_EQ(vectorb(1), b);
}

TEST_F(DynamicVectorFixture, FillElementsDouble) {
  double a = 0.0;
  double b = 1.0;
  vectord.fill({a, b});
  ASSERT_EQ(vectord(0), a);
  ASSERT_EQ(vectord(1), b);
}

TEST_F(DynamicVectorFixture, FillElementsFloat) {
  float a = 0.0;
  float b = 1.0;
  vectorf.fill({a, b});
  ASSERT_EQ(vectorf(0), a);
  ASSERT_EQ(vectorf(1), b);
}

TEST_F(DynamicVectorFixture, FillElementsInt) {
  int a = 0;
  int b = 1;
  vectori.fill({a, b});
  ASSERT_EQ(vectori(0), a);
  ASSERT_EQ(vectori(1), b);
}

TEST_F(DynamicVectorFixture, ArrayiAllEqual) {
  vectori(0) = 1;
  vectori(1) = 2;
  sabai::DynamicVectori new_vectori = vectori;
  ASSERT_TRUE(sabai::all_equal(vectori, new_vectori));
}

TEST_F(DynamicVectorFixture, Size2TypeInt) {
  ASSERT_EQ(vectori.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeInt) {
  int first_value = 1;
  vectori(0) = first_value;
  ASSERT_EQ(vectori(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeDouble) {
  ASSERT_EQ(vectord.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeDouble) {
  double first_value = 1.0;
  vectord(0) = first_value;
  ASSERT_EQ(vectord(0), first_value);
}

TEST_F(DynamicVectorFixture, Size2TypeBool) {
  ASSERT_EQ(vectorb.length(), length);
}

TEST_F(DynamicVectorFixture, SetElementsTypeBool) {
  bool first_value = false;
  vectorb(0) = first_value;
  ASSERT_EQ(vectorb(0), first_value);
}

TEST_F(DynamicVectorFixture, FillBool) {
  bool value = true;
  vectorb.fill(value);
  ASSERT_EQ(vectorb(0), value);
  ASSERT_EQ(vectorb(1), value);
}

TEST_F(DynamicVectorFixture, FillDouble) {
  double value = 1.0;
  vectord.fill(value);
  ASSERT_EQ(vectord(0), value);
  ASSERT_EQ(vectord(1), value);
}

TEST_F(DynamicVectorFixture, FillFloat) {
  float value = 1.0f;
  vectorf.fill(value);
  ASSERT_EQ(vectorf(0), value);
  ASSERT_EQ(vectorf(1), value);
}

TEST_F(DynamicVectorFixture, FillInt) {
  int value = 1;
  vectori.fill(value);
  ASSERT_EQ(vectori(0), value);
  ASSERT_EQ(vectori(1), value);
}

TEST_F(DynamicVectorFixture, IntIndexOutOfRange) {
  ASSERT_THROW(vectori(length), sabai::OutOfRange);
}

class DynamicMatrixFixture : public ::testing::Test {
protected:
  int length[2] = {2, 2};
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;

  sabai::DynamicArrayi<2> matrix;
  sabai::DynamicArrayd<2> matrixd;
  sabai::DynamicArrayf<2> matrixf;

  DynamicMatrixFixture()
      : matrix(length[0], length[1]), matrixd(length[0], length[1]),
        matrixf(length[0], length[1]) {}
};

TEST_F(DynamicMatrixFixture, FillElementsInt) {
  matrix.fill({{a, b}, {c, d}});
  ASSERT_EQ(matrix(0, 0), a);
  ASSERT_EQ(matrix(0, 1), b);
  ASSERT_EQ(matrix(1, 0), c);
  ASSERT_EQ(matrix(1, 1), d);
}

TEST_F(DynamicMatrixFixture, FillElementsDouble) {
  double e = 1.0;
  double f = 2.0;
  double g = 3.0;
  double h = 4.0;

  matrixd.fill({{e, f}, {g, h}});
  ASSERT_EQ(matrixd(0, 0), e);
  ASSERT_EQ(matrixd(0, 1), f);
  ASSERT_EQ(matrixd(1, 0), g);
  ASSERT_EQ(matrixd(1, 1), h);
}

TEST_F(DynamicMatrixFixture, FillElementsFloat) {
  float e = 1.0f;
  float f = 2.0f;
  float g = 3.0f;
  float h = 4.0f;

  matrixf.fill({{e, f}, {g, h}});
  ASSERT_EQ(matrixf(0, 0), e);
  ASSERT_EQ(matrixf(0, 1), f);
  ASSERT_EQ(matrixf(1, 0), g);
  ASSERT_EQ(matrixf(1, 1), h);
}

TEST_F(DynamicMatrixFixture, MatrixIAllEqual) {
  matrix(0, 0) = a;
  matrix(0, 1) = b;
  matrix(1, 0) = c;
  matrix(1, 1) = d;
  sabai::DynamicArrayi<2> new_matrixi = matrix;
  ASSERT_TRUE(sabai::all_equal(new_matrixi, matrix));
}

TEST_F(DynamicMatrixFixture, GetSize) { ASSERT_EQ(matrix.length(), length[0]); }

TEST_F(DynamicMatrixFixture, GetRowSize) {
  ASSERT_EQ(matrix(0).length(), length[1]);
}

TEST_F(DynamicMatrixFixture, SetElementa) {
  matrix(0, 0) = a;
  ASSERT_EQ(matrix(0, 0), a);
}

TEST_F(DynamicMatrixFixture, SetElementb) {
  matrix(0, 1) = b;
  ASSERT_EQ(matrix(0, 1), b);
}

TEST_F(DynamicMatrixFixture, SetElementc) {
  matrix(1, 0) = c;
  ASSERT_EQ(matrix(1, 0), c);
}

TEST_F(DynamicMatrixFixture, SetElementd) {
  matrix(1, 1) = d;
  ASSERT_EQ(matrix(1, 1), d);
}

TEST_F(DynamicMatrixFixture, RowIndexOutOfRange) {
  ASSERT_THROW(matrix(2), sabai::OutOfRange);
}

TEST_F(DynamicMatrixFixture, ElementIndexOutOfRange) {
  ASSERT_THROW(matrix(0, 2), sabai::OutOfRange);
}

TEST_F(DynamicMatrixFixture, RowIndexOutOfRangeElementOk) {
  ASSERT_THROW(matrix(2, 0), sabai::OutOfRange);
}

TEST_F(DynamicMatrixFixture, Filla) {
  matrix.fill(a);
  ASSERT_EQ(matrix(0, 0), a);
  ASSERT_EQ(matrix(0, 1), a);
  ASSERT_EQ(matrix(1, 0), a);
  ASSERT_EQ(matrix(1, 1), a);
}

TEST_F(DynamicMatrixFixture, FillFloat) {
  float value = 3.14f;
  matrixf.fill(value);
  ASSERT_EQ(matrixf(0, 0), value);
  ASSERT_EQ(matrixf(0, 1), value);
  ASSERT_EQ(matrixf(1, 0), value);
  ASSERT_EQ(matrixf(1, 1), value);
}

TEST_F(DynamicMatrixFixture, FillDouble) {
  double value = 3.14;
  matrixd.fill(value);
  ASSERT_EQ(matrixd(0, 0), value);
  ASSERT_EQ(matrixd(0, 1), value);
  ASSERT_EQ(matrixd(1, 0), value);
  ASSERT_EQ(matrixd(1, 1), value);
}

class DynamicTensorFixture : public ::testing::Test {
protected:
  int shape[3] = {2, 2, 2};
  sabai::DynamicArrayi<3> tensor;
  int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};

  DynamicTensorFixture() : tensor(shape[0], shape[1], shape[2]){};
};

TEST_F(DynamicTensorFixture, FillElementsInt) {
  int a = 0;
  int b = 1;
  int c = 2;
  int d = 3;
  int e = 4;
  int f = 5;
  int g = 6;
  int h = 7;
  tensor.fill({{{a, b}, {c, d}}, {{e, f}, {g, h}}});

  ASSERT_EQ(tensor(0, 0, 0), a);
  ASSERT_EQ(tensor(0, 0, 1), b);
  ASSERT_EQ(tensor(0, 1, 0), c);
  ASSERT_EQ(tensor(0, 1, 1), d);
  ASSERT_EQ(tensor(1, 0, 0), e);
  ASSERT_EQ(tensor(1, 0, 1), f);
  ASSERT_EQ(tensor(1, 1, 0), g);
  ASSERT_EQ(tensor(1, 1, 1), h);
}

TEST_F(DynamicTensorFixture, AllEqualTensorInt) {
  tensor(0, 0, 0) = values[0];
  tensor(0, 0, 1) = values[1];
  tensor(0, 1, 0) = values[2];
  tensor(0, 1, 1) = values[3];
  tensor(1, 0, 0) = values[4];
  tensor(1, 0, 1) = values[5];
  tensor(1, 1, 0) = values[6];
  tensor(1, 1, 1) = values[7];
  sabai::DynamicArrayi<3> new_tensori = tensor;
  ASSERT_TRUE(sabai::all_equal(new_tensori, tensor));
}

TEST_F(DynamicTensorFixture, GetSize) { ASSERT_EQ(tensor.length(), shape[0]); }

TEST_F(DynamicTensorFixture, GetMatrix0Size) {
  ASSERT_EQ(tensor(0).length(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetMatrix1Size) {
  ASSERT_EQ(tensor(1).length(), shape[1]);
}

TEST_F(DynamicTensorFixture, GetVectorSize) {
  ASSERT_EQ(tensor(0, 0).length(), shape[2]);
}

TEST_F(DynamicTensorFixture, SetElement) {
  tensor(0, 0, 0) = values[0];
  ASSERT_EQ(tensor(0, 0, 0), values[0]);
}

class EmptyLikeDynamicArray : public ::testing::Test {
protected:
  sabai::DynamicVectori vectori{{1, 2, 3, 4, 5}};
  sabai::DynamicArrayi<2> matrixi{{{1, 2}, {3, 4}}};
};

TEST_F(EmptyLikeDynamicArray, VectorLength) {
  auto empty_vector = sabai::empty_like(vectori);
  ASSERT_EQ(empty_vector.length(), vectori.length());
}

TEST_F(EmptyLikeDynamicArray, VectorTypeSame) {
  auto empty_vector = sabai::empty_like(vectori);
  bool is_same =
      sabai::is_same<decltype(empty_vector), decltype(vectori)>::value;
  ASSERT_TRUE(is_same);
}

TEST_F(EmptyLikeDynamicArray, VectorTypeNotSame) {
  auto empty_vector = sabai::empty_like(vectori);
  bool is_same =
      sabai::is_same<decltype(empty_vector), decltype(matrixi)>::value;
  ASSERT_FALSE(is_same);
}

TEST_F(EmptyLikeDynamicArray, MatrixLength) {
  auto empty_matrix = sabai::empty_like(matrixi);
  ASSERT_EQ(empty_matrix.length(), matrixi.length());
}

TEST_F(EmptyLikeDynamicArray, MatrixRow0Length) {
  auto empty_matrix = sabai::empty_like(matrixi);
  ASSERT_EQ(empty_matrix(0).length(), matrixi(0).length());
}

TEST_F(EmptyLikeDynamicArray, MatrixRow1Length) {
  auto empty_matrix = sabai::empty_like(matrixi);
  ASSERT_EQ(empty_matrix(1).length(), matrixi(1).length());
}

TEST_F(EmptyLikeDynamicArray, MatrixTypeSame) {
  auto empty_matrix = sabai::empty_like(matrixi);
  bool is_same =
      sabai::is_same<decltype(empty_matrix), decltype(matrixi)>::value;
  ASSERT_TRUE(is_same);
}

TEST_F(EmptyLikeDynamicArray, MatrixTypeNotSame) {
  auto empty_matrix = sabai::empty_like(matrixi);
  bool is_same =
      sabai::is_same<decltype(empty_matrix), decltype(vectori)>::value;
  ASSERT_FALSE(is_same);
}

TEST(ARange, ARangeDynamic) {
  auto vector = sabai::ARange(10);
  sabai::DynamicVector<uint64_t> answer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  ASSERT_TRUE(sabai::all_equal(vector, answer));
}