#include "matrix/metrics.hpp"
#include <gtest/gtest.h>

TEST(Metric, Norm_ZeroVectorStatic) {
  sabai::StaticVectord<3> zero_vector(0.0f);
  double norm_vector = sabai::norm(zero_vector);
  ASSERT_DOUBLE_EQ(norm_vector, 0.0);
}

TEST(Metric, Norm_OneVectorStatic) {
  sabai::StaticVectori<3> one_vector(1);
  double norm_vector = sabai::norm(one_vector);
  ASSERT_DOUBLE_EQ(norm_vector, sqrt(3.0));
}

TEST(Metric, Norm_ZeroVectorDynamic) {
  sabai::DynamicVectord zero_vector = {0.0, 0.0, 0.0};
  double norm_vector = sabai::norm(zero_vector);
  ASSERT_DOUBLE_EQ(norm_vector, 0.0);
}

TEST(Metric, Norm_OneVectorDynamic) {
  sabai::DynamicVectori one_vector = {1, 1, 1};
  double norm_vector = sabai::norm(one_vector);
  ASSERT_DOUBLE_EQ(norm_vector, sqrt(3.0));
}