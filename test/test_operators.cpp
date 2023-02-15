#include <gtest/gtest.h>

#include "matrix/dynamic.hpp"
#include "matrix/operators.hpp"
#include "matrix/static.hpp"
#include "matrix/string_representation.hpp"

#include <iostream>

class StaticOperatorFixture : public ::testing::Test {
protected:
  sabai::StaticVectori<3> e1{{1, 0, 0}};
  sabai::StaticVectori<3> e2{{0, 1, 0}};
  sabai::StaticVectori<3> e3{{0, 0, 1}};
  sabai::StaticArrayi<3, 3> matrixi1{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
  sabai::StaticArrayi<3, 3> matrixi2{
      {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}}};
  sabai::StaticArrayi<3, 3> matrixi3{
      {{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}};
};

TEST_F(StaticOperatorFixture, E1EqualsE1) {
  sabai::StaticVector<bool, 3> result = (e1 == e1);
  ASSERT_TRUE(sabai::all(result));
}

TEST_F(StaticOperatorFixture, UnaryMinusMatrix2) {
  sabai::StaticArrayi<3, 3> negative_matrixi2;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      negative_matrixi2(row, col) = -matrixi2(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(negative_matrixi2, -matrixi2));
}

TEST_F(StaticOperatorFixture, UnaryMinusMatrix1) {
  sabai::StaticArrayi<3, 3> negative_matrixi1;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      negative_matrixi1(row, col) = -matrixi1(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(negative_matrixi1, -matrixi1));
}

TEST_F(StaticOperatorFixture, UnaryMinusE1) {
  sabai::StaticVectori<3> negative_e1;
  for (int index = 0; index < 3; ++index) {
    negative_e1(index) = -e1(index);
  }
  ASSERT_TRUE(sabai::all_equal(-e1, negative_e1));
}

TEST_F(StaticOperatorFixture, BinaryPlusMatrix1Matrix2) {
  sabai::StaticArrayi<3, 3> matrix_sum = matrixi1 + matrixi2;
  sabai::StaticArrayi<3, 3> correct_sum;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      correct_sum(row, col) = matrixi1(row, col) + matrixi2(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(matrix_sum, correct_sum));
}

TEST_F(StaticOperatorFixture, BinaryPlusMatrix1Matrix2Matrix3) {
  sabai::StaticArrayi<3, 3> matrix_sum = matrixi1 + matrixi2 + matrixi3;
  sabai::StaticArrayi<3, 3> correct_sum;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      correct_sum(row, col) =
          matrixi1(row, col) + matrixi2(row, col) + matrixi3(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(matrix_sum, correct_sum));
}

TEST_F(StaticOperatorFixture, BinaryPlusE1E2) {
  sabai::StaticVectori<3> my_sum = e1 + e2;
  sabai::StaticVectori<3> correct_sum;
  for (int index = 0; index < 3; ++index) {
    correct_sum(index) = e1(index) + e2(index);
  }
  ASSERT_TRUE(sabai::all_equal(my_sum, correct_sum));
}

TEST_F(StaticOperatorFixture, BinaryPlusE1E2E3) {
  sabai::StaticVectori<3> my_sum = e1 + e2 + e3;
  sabai::StaticVectori<3> correct_sum;
  for (int index = 0; index < 3; ++index) {
    correct_sum(index) = e1(index) + e2(index) + e3(index);
  }
  ASSERT_TRUE(sabai::all_equal(my_sum, correct_sum));
}

TEST_F(StaticOperatorFixture, BinaryMinusMatrix1Matrix2) {
  sabai::StaticArrayi<3, 3> matrix_diff = matrixi1 - matrixi2;
  sabai::StaticArrayi<3, 3> correct_diff;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      correct_diff(row, col) = matrixi1(row, col) - matrixi2(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(matrix_diff, correct_diff));
}

TEST_F(StaticOperatorFixture, BinaryMinusMatrix1Matrix2Matrix3) {
  sabai::StaticArrayi<3, 3> matrix_diff = matrixi1 - matrixi2 - matrixi3;
  sabai::StaticArrayi<3, 3> correct_diff;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      correct_diff(row, col) =
          matrixi1(row, col) - matrixi2(row, col) - matrixi3(row, col);
    }
  }
  ASSERT_TRUE(sabai::all_equal(matrix_diff, correct_diff));
}

TEST_F(StaticOperatorFixture, BinaryMinusE1E2) {
  sabai::StaticVectori<3> my_difference = e1 - e2;
  sabai::StaticVectori<3> correct_difference;
  for (int index = 0; index < 3; ++index) {
    correct_difference(index) = e1(index) - e2(index);
  }
  ASSERT_TRUE(sabai::all_equal(my_difference, correct_difference));
}

TEST_F(StaticOperatorFixture, BinaryMinusE1E2E3) {
  sabai::StaticVectori<3> my_difference = e1 - e2 - e3;
  sabai::StaticVectori<3> correct_difference;
  for (int index = 0; index < 3; ++index) {
    correct_difference(index) = e1(index) - e2(index) - e3(index);
  }
  ASSERT_TRUE(sabai::all_equal(my_difference, correct_difference));
}

TEST_F(StaticOperatorFixture, InPlaceDivision) {
  double a = 3.0;
  sabai::StaticVectord<3> vector(a);
  vector /= a;
  ASSERT_EQ(vector(0), a / a);
  ASSERT_EQ(vector(1), a / a);
  ASSERT_EQ(vector(2), a / a);
}

class DynamicOperatorFixture : public ::testing::Test {
protected:
  int length = 3;
  sabai::DynamicVectori vectori;
  sabai::DynamicVectori vectori2;

  DynamicOperatorFixture() : vectori(length), vectori2(length) {
    vectori(0) = 0;
    vectori(1) = 1;
    vectori(2) = 2;

    vectori2(0) = 0;
    vectori2(1) = 1;
    vectori2(2) = 2;
  }
};

TEST_F(DynamicOperatorFixture, UnaryMinus) {
  sabai::DynamicVectori answer(vectori.length());
  for (int index = 0; index < answer.length(); ++index) {
    answer(index) = -vectori(index);
  }
  ASSERT_TRUE(sabai::all_equal(-vectori, answer));
}

TEST_F(DynamicOperatorFixture, BinaryPlus) {
  sabai::DynamicVectori answer(length);
  for (int index = 0; index < answer.length(); ++index) {
    answer(index) = vectori(index) + vectori2(index);
  }
  ASSERT_TRUE(sabai::all_equal(vectori + vectori2, answer));
}

TEST_F(DynamicOperatorFixture, BinaryMinus) {
  sabai::DynamicVectori answer(length);
  for (int index = 0; index < answer.length(); ++index) {
    answer(index) = vectori(index) - vectori2(index);
  }
  ASSERT_TRUE(sabai::all_equal(vectori - vectori2, answer));
}

TEST_F(DynamicOperatorFixture, InPlaceDivision) {
  double a = 3.0;
  sabai::DynamicVectord vector = {a, a, a};
  vector /= a;
  ASSERT_EQ(vector(0), a / a);
  ASSERT_EQ(vector(1), a / a);
  ASSERT_EQ(vector(2), a / a);
}