#include "matrix/static.hpp"

#include "gtest/gtest.h"

class EmptyStaticArrayFixture: public ::testing::Test
{
        protected:
                math::StaticVectori<2> vector2i;
                math::StaticArrayi<3> vector3i;
                math::StaticVectorf<2> vector2f;
                math::StaticVectorf<3> vector3f;
                math::StaticVectord<2> vector2d;
                math::StaticVectord<3> vector3d;
                math::StaticArrayi<2,2> matrix2i;
                math::StaticArrayf<4,5> matrix45f;
};

TEST_F(EmptyStaticArrayFixture, Matrix45FLength)
{
        int length = matrix45f.length();
        ASSERT_EQ(length, 4);
}

TEST_F(EmptyStaticArrayFixture, Matrix45RowLength)
{
        int length = matrix45f(3).length();
        ASSERT_EQ(length, 5);
}

TEST_F(EmptyStaticArrayFixture, Matrix2iLength)
{
        int length = matrix2i.length();
        ASSERT_EQ(length, 2);
}

TEST_F(EmptyStaticArrayFixture, Matrix2iRowLength)
{
        int length = matrix2i(0).length();
        ASSERT_EQ(length, 2);
}

TEST_F(EmptyStaticArrayFixture, Vector2iLength)
{
        int length = vector2i.length();
        ASSERT_EQ(length, 2);
}

TEST_F(EmptyStaticArrayFixture, Vector3iLength)
{
        int length = vector3i.length();
        ASSERT_EQ(length, 3);
}

TEST_F(EmptyStaticArrayFixture, Vector2fLength)
{
        int length = vector2f.length();
        ASSERT_EQ(length, 2);
}

TEST_F(EmptyStaticArrayFixture, Vector3fLength)
{
        int length = vector3f.length();
        ASSERT_EQ(length, 3);
}

TEST_F(EmptyStaticArrayFixture, Vector2dLength)
{
        int length = vector2d.length();
        ASSERT_EQ(length, 2);
}

TEST_F(EmptyStaticArrayFixture, Vector3dLength)
{
        int length = vector3d.length();
        ASSERT_EQ(length, 3);
}

class OneStaticArrayFixture: public ::testing::Test
{
        protected:
                int valuei = 1;
                math::StaticVectori<2> vector2i;
                math::StaticArrayi<2,2> matrix2i;
                float valuef = 1.0f;
                math::StaticVectorf<4> vector4f;
                float valued = 1.0;
                math::StaticArrayd<1,2> matrix12d;

                OneStaticArrayFixture()
                : vector2i(valuei), matrix2i(valuei),
                  vector4f(valuef), matrix12d(valued)
                {};
};

TEST_F(OneStaticArrayFixture, Matrix12d)
{
        ASSERT_EQ(matrix12d(0,0), valued);
        ASSERT_EQ(matrix12d(0,1), valued);
}

TEST_F(OneStaticArrayFixture, Vector4f)
{
        ASSERT_EQ(vector4f(0), valuef);
        ASSERT_EQ(vector4f(1), valuef);
        ASSERT_EQ(vector4f(2), valuef);
        ASSERT_EQ(vector4f(3), valuef);
}

TEST_F(OneStaticArrayFixture, Vector2i)
{
        ASSERT_EQ(vector2i(0), valuei);
        ASSERT_EQ(vector2i(1), valuei);
}

TEST_F(OneStaticArrayFixture, Matrix2i)
{
        ASSERT_EQ(matrix2i(0,0), valuei);
        ASSERT_EQ(matrix2i(0,1), valuei);
        ASSERT_EQ(matrix2i(1,0), valuei);
        ASSERT_EQ(matrix2i(1,1), valuei);
}

class ZeroStaticArrayFixture: public ::testing::Test
{
        protected:
                int valuei = 0;
                math::StaticVectori<2> vector;
                math::StaticArrayi<2,2> matrix;

                ZeroStaticArrayFixture()
                : vector(valuei), matrix(valuei)
                {};
};

TEST_F(ZeroStaticArrayFixture, Zeros)
{
        ASSERT_EQ(vector(0), valuei);
        ASSERT_EQ(vector(1), valuei);
}

TEST_F(ZeroStaticArrayFixture, AccessElement)
{
        ASSERT_EQ(matrix(0), vector);
}

TEST_F(ZeroStaticArrayFixture, AccessVectorElementOutOfRange)
{
        ASSERT_THROW(vector(2), math::OutOfRange);
}

TEST_F(ZeroStaticArrayFixture, AccessLastElement)
{
        int value = 1;
        vector(1) = value;
        ASSERT_EQ(vector(-1), value);
}

TEST_F(ZeroStaticArrayFixture, AccessMatrixElementOutOfRange)
{
        ASSERT_THROW(matrix(0,2), math::OutOfRange);
}

TEST_F(ZeroStaticArrayFixture, AccessMatrixRowOutOfRange)
{
        ASSERT_THROW(matrix(2), math::OutOfRange);
}

TEST_F(ZeroStaticArrayFixture, AccessElement2)
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

TEST_F(MultiDimensional, AssignElementOutOfRange)
{
        ASSERT_THROW(matrix(2,0) = 6, math::OutOfRange);
}

TEST_F(MultiDimensional, AssignTensorElement)
{
        tensor(0,0,0) = 0;
        ASSERT_EQ(tensor(0,0,0), 0);
}

TEST_F(MultiDimensional, AssignTemsorElementOutofRange)
{
        ASSERT_THROW(tensor(0,2,0) = 0, math::OutOfRange);
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