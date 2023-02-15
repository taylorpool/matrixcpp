#include "sabai/decompositions.hpp"
#include "sabai/string_representation.hpp"

#include <gtest/gtest.h>

#include <cmath>

TEST(DynamicForwardSubstitution, Test1) {
  const sabai::DynamicMatrixd A = {{1.0, 0.0}, {2.0, 1.0}};
  const sabai::DynamicVectord b = {1.0, 4.0};
  const sabai::DynamicVectord correct_answer = {1.0, 2.0};
  auto my_answer = sabai::forward_substitution_solve(A, b);
}

TEST(ForwardSubstitution, Test1) {
  const sabai::StaticArrayd<2, 2> A = {{1.0, 0.0}, {2.0, 1.0}};
  const sabai::StaticArrayd<2> b = {1.0, 4.0};
  const sabai::StaticVectord<2> correct_answer = {1.0, 2.0};
  const auto my_answer = sabai::forward_substitution_solve(A, b);
}

TEST(DynamicBackwardSubstitution, Test1) {
  const sabai::DynamicMatrixd A = {{2.0, 1.0}, {0.0, 1.0}};
  const sabai::DynamicVectord b = {3.0, 1.0};
  const sabai::DynamicVectord correct_answer = {1.0, 1.0};
  const sabai::DynamicVectord my_answer =
      sabai::backward_substitution_solve(A, b);
}

TEST(BackwardSubstitution, Test1) {
  const sabai::StaticArrayd<2, 2> A = {{2.0, 1.0}, {0.0, 1.0}};
  const sabai::StaticVectord<2> b = {3.0, 1.0};
  const sabai::StaticVectord<2> correct_answer = {1.0, 1.0};
  const sabai::StaticVectord<2> my_answer =
      sabai::backward_substitution_solve(A, b);
}

TEST(DynamicCholesky, Test1) {
  const sabai::DynamicMatrixd A = {{1.0, 0.0}, {0.0, 4.0}};
  const sabai::DynamicMatrixd U_correct = {{sqrt(A(0, 0)), 0.0},
                                           {0.0, sqrt(A(1, 1))}};
  const sabai::DynamicVectord b = {1.0, 4.0};
  const sabai::DynamicVectord x_correct = {b(0) / A(0, 0), b(1) / A(1, 1)};
  const sabai::DynamicCholeskyDecomposition cholesky(A);

  ASSERT_TRUE(sabai::all_equal(U_correct, cholesky.cholesky));
  ASSERT_TRUE(sabai::all_equal(x_correct, sabai::solve(cholesky, b)));
}

TEST(Cholesky, Test1) {
  const sabai::StaticArrayd<2, 2> A = {{1.0, 0.0}, {0.0, 4.0}};
  const sabai::StaticArrayd<2, 2> U_correct = {{sqrt(A(0, 0)), 0.0},
                                               {0.0, sqrt(A(1, 1))}};
  const sabai::StaticVectord<2> b = {1.0, 4.0};
  const sabai::StaticVectord<2> x_correct = {b(0) / A(0, 0), b(1) / A(1, 1)};
  const sabai::CholeskyDecomposition cholesky(A);

  ASSERT_TRUE(sabai::all_equal(U_correct, cholesky.cholesky));
  const auto solution = sabai::solve(cholesky, b);
  ASSERT_TRUE(sabai::all_equal(x_correct, sabai::solve(cholesky, b)));
}

TEST(DynamicLUDecomposition, Test1) {
  const sabai::DynamicMatrixd A = {
      {1.0, 1.0, 1.0}, {1.0, 4.0, 2.0}, {4.0, 7.0, 8.0}};
  const sabai::DynamicVectord b = {1.0, 3.0, 9.0};
  const sabai::DynamicLUDecomposition lu(A);
  ASSERT_TRUE(sabai::all_equal(A(lu.P), lu.L * lu.U));
  const auto solution = sabai::solve(lu, b);
  const auto v = A * solution;
  ASSERT_TRUE(sabai::all_equal(A * solution, b));
}

TEST(LUDecomposition, Test1) {
  sabai::StaticArrayd<3, 3> A = {
      {1.0, 1.0, 1.0}, {1.0, 4.0, 2.0}, {4.0, 7.0, 8.0}};

  sabai::StaticVectord<3> b = {1.0, 3.0, 9.0};

  sabai::LUDecomposition lu(A);
  ASSERT_TRUE(sabai::all_equal(A(lu.P), lu.L * lu.U));
  auto solution = sabai::solve(lu, b);
  ASSERT_TRUE(sabai::all_equal(A * solution, b));
}

TEST(QRDecomposition, Static) {
  auto A = sabai::Identity<double, 3>();
  sabai::QRDecomposition qr(A);
  ASSERT_TRUE(sabai::all_equal(qr.Q * qr.R, A));
}

TEST(QRDecomposition, Dynamic) {
  auto A = sabai::Identity<double>(3);
  sabai::DynamicQRDecomposition qr(A);
  ASSERT_TRUE(sabai::all_equal(qr.Q * qr.R, A));
}

TEST(SwapElements, Integers) {
  int a = 1;
  int b = 2;
  sabai::swap(a, b);
  ASSERT_EQ(a, 2);
  ASSERT_EQ(b, 1);
}

TEST(SwapElements, Vector) {
  sabai::StaticVectori<2> x = {1, 2};
  sabai::swap(x(0), x(1));
  ASSERT_EQ(x(0), 2);
  ASSERT_EQ(x(1), 1);
}