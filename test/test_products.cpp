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

class ProductFixture: public ::testing::Test
{
    protected:
        math::StaticVectori<3> e1{{1, 0, 0}};
        math::StaticVectori<3> e2{{0, 1, 0}};
        math::StaticVectori<3> e3{{0, 0, 1}};
};

TEST_F(ProductFixture, E1CrossE2_E3)
{
    ASSERT_TRUE(math::all_equal(math::cross(e1, e2), e3));
}

TEST_F(ProductFixture, NegE2CrossE1_E3)
{
    ASSERT_TRUE(math::all_equal(math::cross(-e2, e1), e3));
}

TEST_F(ProductFixture, DistributiveCrossProduct)
{
    decltype(e1) left = math::cross(e1, math::cross(e2,e3));
    decltype(e1) right = math::dot(e1, e3)*e2 - math::dot(e1, e2)*e3;
    ASSERT_TRUE(math::all_equal(left, right));
}

TEST_F(ProductFixture, DistributiveDotOnCrossProduct1)
{
    int result1 = math::dot(e1, math::cross(e2, e3));
    int result2 = math::dot(e3, math::cross(e1, e2));
    ASSERT_EQ(result1, result2);
}

TEST_F(ProductFixture, DistributiveDotOnCrossProduct2)
{
    int result2 = math::dot(e3, math::cross(e1, e2));
    int result3 = math::dot(e2, math::cross(e3, e1));
    ASSERT_EQ(result2, result3);
}

TEST(Multiply, ArrayVector)
{
        auto matrix = math::StaticArray<int, 2, 2>(1);
        auto vector = math::StaticVector<int, 2>(1);
        decltype(vector) result = matrix*vector;
        math::StaticVectori<2> correct = {
            matrix(0,0)*vector(0)+matrix(0,1)*vector(1),
            matrix(1,0)*vector(0)+matrix(1,1)*vector(1)
        };
        ASSERT_TRUE(math::all_equal(result, correct));
}

TEST(Multiply, ArrayArray)
{
        auto A = math::StaticArray<int, 2, 2>(1);
        auto B = math::StaticArray<int, 2, 2>(1);
        decltype(A) result = A*B;
        math::StaticArray<int, 2, 2> answer = {
            {A(0,0)*B(0,0)+A(0,1)*B(1,0), A(0,0)*B(0,1)+A(0,1)*B(1,1)},
            {A(1,0)*B(0,0)+A(1,1)*B(1,0), A(1,0)*B(0,1)+A(1,1)*B(1,1)},
        };
        ASSERT_TRUE(math::all_equal(result, answer));
}

TEST(OuterProduct, VectorVector)
{
    math::StaticVectori<2> vector1 = {1, 2};
    math::StaticVectori<2> vector2 = {3, 4};
    math::StaticArrayi<2,2> answer = {
        {vector1(0)*vector2(0), vector1(0)*vector2(1)},
        {vector1(1)*vector2(0), vector1(1)*vector2(1)}
    };
    ASSERT_TRUE(math::all_equal(math::outer(vector1, vector2), answer));
}