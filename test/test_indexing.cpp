#include "matrix/indexing.hpp"
#include "matrix/operators.hpp"

#include <gtest/gtest.h>

class StaticIndexingFixture : public ::testing::Test {
protected:
  sabai::StaticArrayi<2, 2> A = {{1, 2}, {3, 4}};
  sabai::StaticArrayi<3, 3> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  sabai::StaticVectori<5> vector = {0, 1, 2, 3, 4};
};

TEST_F(StaticIndexingFixture, UpperTriangularA) {
  sabai::StaticArrayi<2, 2> B(A);
  B(1, 0) = 0;
  ASSERT_TRUE(sabai::all_equal(B, sabai::triu(A)));
}

TEST_F(StaticIndexingFixture, UpperTriangularMatrix) {
  sabai::StaticArrayi<3, 3> upper_matrix(matrix);
  upper_matrix(1, 0) = 0;
  upper_matrix(2, 0) = 0;
  upper_matrix(2, 1) = 0;
  ASSERT_TRUE(sabai::all_equal(upper_matrix, sabai::triu(matrix)));
}

TEST_F(StaticIndexingFixture, LowerTriangular) {
  sabai::StaticArrayi<2, 2> B(A);
  B(0, 1) = 0;
  ASSERT_TRUE(sabai::all_equal(B, sabai::tril(A)));
}

TEST_F(StaticIndexingFixture, LowerTriangularMatrix) {
  sabai::StaticArrayi<3, 3> lower_matrix(matrix);
  lower_matrix(0, 1) = 0;
  lower_matrix(0, 2) = 0;
  lower_matrix(1, 2) = 0;
  ASSERT_TRUE(sabai::all_equal(lower_matrix, sabai::tril(matrix)));
}
TEST_F(StaticIndexingFixture, SliceVector) {
  auto vector_slice = sabai::slice<0, 3>(vector);
  sabai::StaticVectori<3> answer = {0, 1, 2};
  ASSERT_TRUE(sabai::all_equal(vector_slice, answer));
}

TEST_F(StaticIndexingFixture, SliceMatrix) {
  auto matrix_slice = sabai::slice<0, 2>(matrix);
  sabai::StaticArrayi<2, 3> answer = {
      {matrix(0, 0), matrix(0, 1), matrix(0, 2)},
      {matrix(1, 0), matrix(1, 1), matrix(1, 2)}};
  ASSERT_TRUE(sabai::all_equal(matrix_slice, answer));
}

class DynamicIndexingFixture : public ::testing::Test {
protected:
  sabai::DynamicMatrixi A = {{1, 2}, {3, 4}};
  sabai::DynamicMatrixi matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  sabai::DynamicVectori vector = {0, 1, 2, 3, 4};
};

TEST_F(DynamicIndexingFixture, UpperTriangularA) {
  sabai::DynamicMatrixi B(A);
  B(1, 0) = 0;
  ASSERT_TRUE(sabai::all_equal(B, sabai::triu(A)));
}

TEST_F(DynamicIndexingFixture, UpperTriangularMatrix) {
  sabai::DynamicMatrixi upper_matrix(matrix);
  upper_matrix(1, 0) = 0;
  upper_matrix(2, 0) = 0;
  upper_matrix(2, 1) = 0;
  ASSERT_TRUE(sabai::all_equal(upper_matrix, sabai::triu(matrix)));
}

TEST_F(DynamicIndexingFixture, LowerTriangular) {
  sabai::DynamicMatrixi B(A);
  B(0, 1) = 0;
  ASSERT_TRUE(sabai::all_equal(B, sabai::tril(A)));
}

TEST_F(DynamicIndexingFixture, LowerTriangularMatrix) {
  sabai::DynamicMatrixi lower_matrix(matrix);
  lower_matrix(0, 1) = 0;
  lower_matrix(0, 2) = 0;
  lower_matrix(1, 2) = 0;
  ASSERT_TRUE(sabai::all_equal(lower_matrix, sabai::tril(matrix)));
}