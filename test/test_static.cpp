#include "matrix/static.hpp"

#include "gtest/gtest.h"

class ZeroStaticArrayFixture: public ::testing::Test
{
        protected:
                math::StaticVectori<2> vector2i;
                math::StaticArrayi<3> vector3i;
                math::StaticVectorf<2> vector2f;
                math::StaticVectorf<3> vector3f;
                math::StaticVectord<2> vector2d;
                math::StaticVectord<3> vector3d;
};

TEST(ZeroArray, Vector)
{
        int initial_value = 0;
        math::StaticVectori<2> vector(initial_value);
        ASSERT_EQ(vector(0), initial_value);
        ASSERT_EQ(vector(1), initial_value);
}

TEST_F(ZeroStaticArrayFixture, Vector2iShape)
{
        math::StaticVectori<1> shape = vector2i.shape();
        ASSERT_EQ(shape(0), 2);
}

TEST_F(ZeroStaticArrayFixture, Vector3iShape)
{
        math::StaticVectori<1> shape = vector3i.shape();
        ASSERT_EQ(shape(0), 3);
}

TEST_F(ZeroStaticArrayFixture, Vector2fShape)
{
        math::StaticVectori<1> shape = vector2f.shape();
        ASSERT_EQ(shape(0), 2);
}

TEST_F(ZeroStaticArrayFixture, Vector3fShape)
{
        math::StaticVectori<1> shape = vector3f.shape();
        ASSERT_EQ(shape(0), 3);
}

TEST_F(ZeroStaticArrayFixture, Vector2dShape)
{
        math::StaticVectori<1> shape = vector2d.shape();
        ASSERT_EQ(shape(0), 2);
}

TEST_F(ZeroStaticArrayFixture, Vector3dShape)
{
        math::StaticVectori<1> shape = vector3d.shape();
        ASSERT_EQ(shape(0), 3);
}

TEST(ZeroArray, Vector3Shape)
{
        math::StaticVectori<3> vector;
        math::StaticVectori<1> shape = vector.shape();
        ASSERT_EQ(shape(0), 3);
}

TEST(ZeroArray, Matrix2)
{
        int initial_value = 0;
        math::StaticArrayi<2,2> matrix(0);
        ASSERT_EQ(matrix(0,0), initial_value);
        ASSERT_EQ(matrix(0,1), initial_value);
        ASSERT_EQ(matrix(1,0), initial_value);
        ASSERT_EQ(matrix(1,1), initial_value);
}

TEST(ZeroArray, Matrix2Shape)
{
        math::StaticArrayi<2,2> matrix;
        math::StaticVectori<2> shape = matrix.shape();
}

TEST(OneArray, Vector)
{
        int initial_value = 1;
        math::StaticVectori<2> vector(initial_value);
        ASSERT_EQ(vector(0), 1);
        ASSERT_EQ(vector(1), 1);
}

TEST(OneArray, Matrix)
{
        int initial_value = 1;
        math::StaticArrayi<2,2> matrix(initial_value);
        ASSERT_EQ(matrix(0,0), initial_value);
        ASSERT_EQ(matrix(0,1), initial_value);
        ASSERT_EQ(matrix(1,0), initial_value);
        ASSERT_EQ(matrix(1,1), initial_value);
}

class ZeroMatricies: public ::testing::Test
{
        protected:
                math::StaticVectori<2> vector{math::StaticVectori<2>(0)};
                math::StaticArrayi<2,2> matrix{math::StaticArrayi<2,2>(0)};
};

TEST_F(ZeroMatricies, Zeros)
{
        ASSERT_EQ(vector(0), 0);
        ASSERT_EQ(vector(1), 0);
}

TEST_F(ZeroMatricies, AccessElement)
{
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(ZeroMatricies, AccessElement2)
{
        auto ans = math::StaticVectori<2>(1);
        ASSERT_NE(matrix(0), ans);
}

class MultiDimensional: public ::testing::Test
{
        protected:
                math::StaticVectori<2> vector{{1, 2}};
                math::StaticArrayi<2, 2> matrix{{
                        {1, 2},
                        {3, 4}
                }};
                math::StaticArrayi<2, 2, 2> tensor{{
                        {
                                {1, 2},
                                {3, 4}
                        },
                        {
                                {5, 6},
                                {7, 8}
                        }
                }};
};

TEST_F(MultiDimensional, CreateVector)
{
        ASSERT_EQ(vector(0), 1);
        ASSERT_EQ(vector(1), 2);
}

TEST_F(MultiDimensional, CreateArray)
{
        ASSERT_EQ(matrix(0,0), 1);
        ASSERT_EQ(matrix(0,1), 2);
        ASSERT_EQ(matrix(1,0), 3);
        ASSERT_EQ(matrix(1,1), 4);
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(MultiDimensional, AssignElement)
{
        matrix(0,0) = 6;
        ASSERT_EQ(matrix(0,0), 6);
}

TEST_F(MultiDimensional, AssignTensorElement)
{
        tensor(0,0,0) = 0;
        ASSERT_EQ(tensor(0,0,0), 0);
}

TEST_F(MultiDimensional, GetFirstTensorArray)
{
        ASSERT_EQ(tensor(0), matrix);
}

TEST_F(MultiDimensional, GetFirstTensorVector)
{
        ASSERT_EQ(tensor(0,0), vector);
}

TEST_F(MultiDimensional, SetFirstTensorVector)
{
        math::StaticVectori<2> new_vector = {{100, 101}};
        ASSERT_NE(tensor(0,0), new_vector);
        tensor(0,0) = new_vector;
        ASSERT_EQ(tensor(0,0), new_vector);
}

TEST_F(MultiDimensional, MatrixIncrement)
{
        matrix(0,0) += 1;
        ASSERT_EQ(matrix(0,0), 2);
}

TEST(Identity, Matrix)
{
        auto matrix = math::Identity<int, 2>();
        decltype(matrix) answer = {
                {1, 0},
                {0, 1}
        };
        ASSERT_EQ(matrix, answer);
}

TEST(ARange, Vector)
{
        auto range = math::ARange<4>();
        math::StaticVectori<4> answer = {
                0, 1, 2, 3
        };
        ASSERT_EQ(range, answer);
}

TEST_F(MultiDimensional, IndexingVector)
{
        math::StaticVectori<1> indices = {1};
        math::StaticVectori<1> answer = {vector(indices(0))};
        ASSERT_EQ(answer, vector(indices));
}

TEST_F(MultiDimensional, IndexingMatrix)
{
        math::StaticVectori<1> indices = {1};
        math::StaticArrayi<1,2> answer = {
                {3, 4}
        };
        ASSERT_EQ(answer, matrix(indices));
}