#include "matrix/products.hpp"
#include "matrix/dynamic.hpp"

#include "gtest/gtest.h"

class ScalarProductVector: public ::testing::Test
{
    protected:
        int factor = 10;
        math::DynamicVectori dynamic_vector = {1,2};
        math::StaticVectori<2> static_vector = {1,2};
};

TEST_F(ScalarProductVector, DynamicVectorScalar)
{
    decltype(dynamic_vector) answer = {
        factor*dynamic_vector(0),
        factor*dynamic_vector(1)
        };
    ASSERT_TRUE(math::all_equal(dynamic_vector*factor, answer));
}

TEST_F(ScalarProductVector, ScalarDynamicVector)
{
    decltype(dynamic_vector) answer = {
        factor*dynamic_vector(0),
        factor*dynamic_vector(1)
        };
    ASSERT_TRUE(math::all_equal(factor*dynamic_vector, answer));
}

TEST_F(ScalarProductVector, ScalarStaticVector)
{
    decltype(static_vector) answer = {
        factor*static_vector(0),
        factor*static_vector(1)
        };
    ASSERT_TRUE(math::all_equal(factor*static_vector, answer));
}

TEST_F(ScalarProductVector, StaticVectorScalar)
{
    decltype(static_vector) answer = {
        factor*static_vector(0), factor*static_vector(1)
        };
    ASSERT_TRUE(math::all_equal(static_vector*factor, answer));
}

class ScalarProductMatrix: public ::testing::Test
{
    protected:
        int factor = 10;
        math::StaticArrayi<2,2> static_matrix = {
            {1, 2},
            {3, 4}
        };
        math::DynamicArrayi<2> dynamic_matrix = {
            {1, 2},
            {3, 4}
        };
};

TEST_F(ScalarProductMatrix, ScalarDynamicMatrix)
{
    decltype(dynamic_matrix) answer = {
        {factor*dynamic_matrix(0,0), factor*dynamic_matrix(0,1)},
        {factor*dynamic_matrix(1,0), factor*dynamic_matrix(1,1)}
    };
    decltype(dynamic_matrix) my_answer = factor*dynamic_matrix;
    ASSERT_TRUE(math::all_equal(my_answer, answer));
}

TEST_F(ScalarProductMatrix, DynamicMatrixScalar)
{
    decltype(dynamic_matrix) answer = {
        {factor*dynamic_matrix(0,0), factor*dynamic_matrix(0,1)},
        {factor*dynamic_matrix(1,0), factor*dynamic_matrix(1,1)}
    };
    decltype(dynamic_matrix) my_answer = dynamic_matrix*factor;
    ASSERT_TRUE(math::all_equal(my_answer, answer));
}

TEST_F(ScalarProductMatrix, ScalarStaticMatrix)
{
    decltype(static_matrix) answer = {
        {factor*static_matrix(0,0), factor*static_matrix(0,1)},
        {factor*static_matrix(1,0), factor*static_matrix(1,1)}
    };
    ASSERT_TRUE(math::all_equal(factor*static_matrix, answer));
}

TEST_F(ScalarProductMatrix, StaticMatrixScalar)
{
    decltype(static_matrix) answer = {
        {factor*static_matrix(0,0), factor*static_matrix(0,1)},
        {factor*static_matrix(1,0), factor*static_matrix(1,1)}
    };
    ASSERT_TRUE(math::all_equal(static_matrix*factor, answer));
}

class ScalarProductTensor: public ::testing::Test
{
    protected:
        math::StaticArrayi<2,2,2> static_tensor = {
            {
                {1, 2},
                {3, 4}
            },
            {
                {5, 6},
                {7, 8}
            }
        };
        math::DynamicArrayi<3> dynamic_tensor = {
            {
                {1, 2},
                {3, 4}
            },
            {
                {5, 6},
                {7, 8}
            }
        };
        int factor = 10;
};

TEST_F(ScalarProductTensor, ScalarDynamicTensor)
{
    decltype(dynamic_tensor) product = factor*dynamic_tensor;
    decltype(dynamic_tensor) correct_answer = {
        {
            {factor*dynamic_tensor(0,0,0), factor*dynamic_tensor(0,0,1)},
            {factor*dynamic_tensor(0,1,0), factor*dynamic_tensor(0,1,1)}
        },
        {
            {factor*dynamic_tensor(1,0,0), factor*dynamic_tensor(1,0,1)},
            {factor*dynamic_tensor(1,1,0), factor*dynamic_tensor(1,1,1)}
        }
    };
    ASSERT_TRUE(math::all_equal(product, correct_answer));
}

TEST_F(ScalarProductTensor, DynamicTensorScalar)
{
    decltype(dynamic_tensor) product = dynamic_tensor*factor;
    decltype(dynamic_tensor) correct_answer = {
        {
            {factor*dynamic_tensor(0,0,0), factor*dynamic_tensor(0,0,1)},
            {factor*dynamic_tensor(0,1,0), factor*dynamic_tensor(0,1,1)}
        },
        {
            {factor*dynamic_tensor(1,0,0), factor*dynamic_tensor(1,0,1)},
            {factor*dynamic_tensor(1,1,0), factor*dynamic_tensor(1,1,1)}
        }
    };
    ASSERT_TRUE(math::all_equal(product, correct_answer));
}

TEST_F(ScalarProductTensor, ScalarStaticTensor)
{
    decltype(static_tensor) product = factor*static_tensor;
    decltype(static_tensor) correct_answer = {
        {
            {factor*static_tensor(0,0,0), factor*static_tensor(0,0,1)},
            {factor*static_tensor(0,1,0), factor*static_tensor(0,1,1)}
        },
        {
            {factor*static_tensor(1,0,0), factor*static_tensor(1,0,1)},
            {factor*static_tensor(1,1,0), factor*static_tensor(1,1,1)}
        }
    };
    ASSERT_TRUE(math::all_equal(product, correct_answer));
}

TEST_F(ScalarProductTensor, StaticTensorScalar)
{
    decltype(static_tensor) product = static_tensor*factor;
    decltype(static_tensor) correct_answer = {
        {
            {factor*static_tensor(0,0,0), factor*static_tensor(0,0,1)},
            {factor*static_tensor(0,1,0), factor*static_tensor(0,1,1)}
        },
        {
            {factor*static_tensor(1,0,0), factor*static_tensor(1,0,1)},
            {factor*static_tensor(1,1,0), factor*static_tensor(1,1,1)}
        }
    };
    ASSERT_TRUE(math::all_equal(product, correct_answer));
}

class DotProductFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<3> e1_static = {1, 0, 0};
        math::StaticVectori<3> e2_static = {0, 1, 0};
        math::StaticVectori<3> e3_static = {0, 0, 1};
        math::DynamicVectori e1_dynamic = {1, 0, 0};
        math::DynamicVectori e2_dynamic = {0, 1, 0};
        math::DynamicVectori e3_dynamic = {0, 0, 1};
};

TEST_F(DotProductFixture, StaticE1E2_0)
{
    ASSERT_EQ(math::dot(e1_static, e2_static), 0);
}

TEST_F(DotProductFixture, StaticE1E3_0)
{
    ASSERT_EQ(math::dot(e1_static, e3_static), 0);
}

TEST_F(DotProductFixture, StaticE1E1_1)
{
    ASSERT_EQ(math::dot(e1_static, e1_static), 1);
}

TEST_F(DotProductFixture, StaticE2E2_1)
{
    ASSERT_EQ(math::dot(e2_static, e2_static), 1);
}

TEST_F(DotProductFixture, StaticE3E3_1)
{
    ASSERT_EQ(math::dot(e3_static, e3_static), 1);
}

TEST_F(DotProductFixture, DynamicE1E2_0)
{
    ASSERT_EQ(math::dot(e1_dynamic, e2_dynamic), 0);
}

TEST_F(DotProductFixture, DynamicE1E3_0)
{
    ASSERT_EQ(math::dot(e1_dynamic, e3_dynamic), 0);
}

TEST_F(DotProductFixture, DynamicE1_WrongLength_MisMatchedLength)
{
    math::DynamicVector<int> vector = {0,1};
    ASSERT_THROW(math::dot(e1_dynamic, vector), math::MismatchedLength);
}

TEST_F(DotProductFixture, DynamicE1E1_1)
{
    ASSERT_EQ(math::dot(e1_dynamic, e1_dynamic), 1);
}

TEST_F(DotProductFixture, DynamicE2E2_1)
{
    ASSERT_EQ(math::dot(e2_dynamic, e2_dynamic), 1);
}

TEST_F(DotProductFixture, DynamicE3E3_1)
{
    ASSERT_EQ(math::dot(e3_dynamic, e3_dynamic), 1);
}

class CrossProductFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<3> e1_static = {1, 0, 0};
        math::StaticVectori<3> e2_static = {0, 1, 0};
        math::StaticVectori<3> e3_static = {0, 0, 1};
        math::DynamicVectori e1_dynamic = {1, 0, 0};
        math::DynamicVectori e2_dynamic = {0, 1, 0};
        math::DynamicVectori e3_dynamic = {0, 0, 1};
};

TEST_F(CrossProductFixture, StaticE1CrossE2_E3)
{
    ASSERT_TRUE(math::all_equal(math::cross(e1_static, e2_static), e3_static));
}

TEST_F(CrossProductFixture, StaticE2CrossE3_E1)
{
    ASSERT_TRUE(math::all_equal(math::cross(e2_static, e3_static), e1_static));
}

TEST_F(CrossProductFixture, StaticE3CrossE1_E2)
{
    ASSERT_TRUE(math::all_equal(math::cross(e3_static, e1_static), e2_static));
}

TEST_F(CrossProductFixture, StaticE2CrossE1_NegE3)
{
    ASSERT_TRUE(math::all_equal(math::cross(e2_static, e1_static), -e3_static));
}

TEST_F(CrossProductFixture, StaticE3CrossE2_NegE1)
{
    ASSERT_TRUE(math::all_equal(math::cross(e3_static, e2_static), -e1_static));
}

TEST_F(CrossProductFixture, StaticE1CrossE3_NegE2)
{
    ASSERT_TRUE(math::all_equal(math::cross(e1_static, e3_static), -e2_static));
}

TEST_F(CrossProductFixture, DynamicE1CrossE2_E3)
{
    ASSERT_TRUE(math::all_equal(math::cross(e1_dynamic, e2_dynamic), e3_dynamic));
}

TEST_F(CrossProductFixture, DynamicE2CrossE3_E1)
{
    ASSERT_TRUE(math::all_equal(math::cross(e2_dynamic, e3_dynamic), e1_dynamic));
}

TEST_F(CrossProductFixture, DynamicE3CrossE1_E2)
{
    ASSERT_TRUE(math::all_equal(math::cross(e3_dynamic, e1_dynamic), e2_dynamic));
}

TEST_F(CrossProductFixture, DynamicE2CrossE1_NegE3)
{
    ASSERT_TRUE(math::all_equal(math::cross(e2_dynamic, e1_dynamic), -e3_dynamic));
}

TEST_F(CrossProductFixture, DynamicE3CrossE2_NegE1)
{
    ASSERT_TRUE(math::all_equal(math::cross(e3_dynamic, e2_dynamic), -e1_dynamic));
}

TEST_F(CrossProductFixture, DynamicE1CrossE3_NegE2)
{
    ASSERT_TRUE(math::all_equal(math::cross(e1_dynamic, e3_dynamic), -e2_dynamic));
}

class DotCrossProductFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<3> e1_static = {1, 0, 0};
        math::StaticVectori<3> e2_static = {0, 1, 0};
        math::StaticVectori<3> e3_static = {0, 0, 1};
        math::DynamicVectori e1_dynamic = {1, 0, 0};
        math::DynamicVectori e2_dynamic = {0, 1, 0};
        math::DynamicVectori e3_dynamic = {0, 0, 1};
};

TEST_F(DotCrossProductFixture, DistributiveDynamicCrossProduct)
{
    decltype(e1_dynamic) left = math::cross(e1_dynamic, math::cross(e2_dynamic,e3_dynamic));
    decltype(e1_dynamic) right = math::dot(e1_dynamic, e3_dynamic)*e2_dynamic - math::dot(e1_dynamic, e2_dynamic)*e3_dynamic;
    ASSERT_TRUE(math::all_equal(left, right));
}

TEST_F(DotCrossProductFixture, DistributiveDynamicDotOnCrossProduct1)
{
    int result1 = math::dot(e1_dynamic, math::cross(e2_dynamic, e3_dynamic));
    int result2 = math::dot(e3_dynamic, math::cross(e1_dynamic, e2_dynamic));
    ASSERT_EQ(result1, result2);
}

TEST_F(DotCrossProductFixture, DistributiveDynamicDotOnCrossProduct2)
{
    int result2 = math::dot(e3_dynamic, math::cross(e1_dynamic, e2_dynamic));
    int result3 = math::dot(e2_dynamic, math::cross(e3_dynamic, e1_dynamic));
    ASSERT_EQ(result2, result3);
}
TEST_F(DotCrossProductFixture, DistributiveStaticCrossProduct)
{
    decltype(e1_static) left = math::cross(e1_static, math::cross(e2_static,e3_static));
    decltype(e1_static) right = math::dot(e1_static, e3_static)*e2_static - math::dot(e1_static, e2_static)*e3_static;
    ASSERT_TRUE(math::all_equal(left, right));
}

TEST_F(DotCrossProductFixture, DistributiveStaticDotOnCrossProduct1)
{
    int result1 = math::dot(e1_static, math::cross(e2_static, e3_static));
    int result2 = math::dot(e3_static, math::cross(e1_static, e2_static));
    ASSERT_EQ(result1, result2);
}

TEST_F(DotCrossProductFixture, DistributiveStaticDotOnCrossProduct2)
{
    int result2 = math::dot(e3_static, math::cross(e1_static, e2_static));
    int result3 = math::dot(e2_static, math::cross(e3_static, e1_static));
    ASSERT_EQ(result2, result3);
}

class MultiplyMatrixFixture: public ::testing::Test
{
    protected:
        math::StaticArrayi<2, 2> static_matrix = 1;
        math::StaticVectori<2> static_vector = 1;
        math::DynamicArrayi<2> dynamic_matrix = {
            {1, 1},
            {1, 1}
        };
        math::DynamicVectori dynamic_vector = {1, 1};
};

TEST_F(MultiplyMatrixFixture, DynamicMatrixVector)
{
    math::DynamicVectori result = dynamic_matrix*dynamic_vector;
    math::DynamicVectori answer = {
        dynamic_matrix(0,0)*dynamic_vector(0) + dynamic_matrix(0,1)*dynamic_vector(1),
        dynamic_matrix(1,0)*dynamic_vector(0) + dynamic_matrix(1,1)*dynamic_vector(1)
    };
    ASSERT_TRUE(math::all_equal(result, answer));
}

TEST_F(MultiplyMatrixFixture, DynamicMatrixMatrix)
{
    auto A = dynamic_matrix;
    auto B = dynamic_matrix;
    math::DynamicArrayi<2> result = dynamic_matrix*dynamic_matrix;
    math::DynamicArrayi<2> answer = {
        {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
        {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)},
    };
    ASSERT_TRUE(math::all_equal(answer, result));
}

TEST_F(MultiplyMatrixFixture, StaticMatrixVector)
{
    math::StaticVectori<2> result = static_matrix*static_vector;
    math::StaticVectori<2> answer = {
        static_matrix(0,0)*static_vector(0) + static_matrix(0,1)*static_vector(1),
        static_matrix(1,0)*static_vector(0) + static_matrix(1,1)*static_vector(1)
    };
    ASSERT_TRUE(math::all_equal(result, answer));
}

TEST_F(MultiplyMatrixFixture, StaticMatrixMatrix)
{
    math::StaticArrayi<2,2> result = static_matrix*static_matrix;
    auto A = static_matrix;
    auto B = static_matrix;
    math::StaticArrayi<2,2> answer = {
        {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
        {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)}
    };
    ASSERT_TRUE(math::all_equal(result, answer));
}

class OuterProductFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<2> static_vector1 = {1, 2};
        math::StaticVectori<2> static_vector2 = {3, 4};
        math::DynamicVectori dynamic_vector1 = {1, 2};
        math::DynamicVectori dynamic_vector2 = {3, 4};
};

TEST_F(OuterProductFixture, StaticVectorVector)
{
    math::StaticArrayi<2,2> result = math::outer(static_vector1, static_vector2);
    math::StaticArrayi<2,2> answer = {
        {static_vector1(0)*static_vector2(0), static_vector1(0)*static_vector2(1)},
        {static_vector1(1)*static_vector2(0), static_vector1(1)*static_vector2(1)}
    };
    ASSERT_TRUE(math::all_equal(result, answer));
}

TEST_F(OuterProductFixture, DynamicVectorVector)
{
    math::DynamicMatrixi result = math::outer(dynamic_vector1, dynamic_vector2);
    math::DynamicMatrixi answer = {
        {dynamic_vector1(0)*dynamic_vector2(0), dynamic_vector1(0)*dynamic_vector2(1)},
        {dynamic_vector1(1)*dynamic_vector2(0), dynamic_vector1(1)*dynamic_vector2(1)}
    };
    ASSERT_TRUE(math::all_equal(result, answer));
}