#include "matrix/decompositions.hpp"
#include "matrix/string_representation.hpp"

#include <gtest/gtest.h>

#include <cmath>

TEST(DynamicForwardSubstitution, Test1)
{
    math::DynamicMatrixd A = {
        {1.0, 0.0},
        {2.0, 1.0}
    };
    math::DynamicVectord b = {
        1.0, 4.0
    };
    math::DynamicVectord correct_answer = {
        1.0, 2.0
    };
    auto my_answer = math::forward_substitution_solve(A, b);
}

TEST(ForwardSubstitution, Test1)
{
    math::StaticArrayd<2,2> A = {
        {1.0, 0.0},
        {2.0, 1.0}
    };
    math::StaticArrayd<2> b = {
        1.0, 4.0
    };
    math::StaticVectord<2> correct_answer = {
        1.0, 2.0
    };
    auto my_answer = math::forward_substitution_solve(A, b);
}

TEST(DynamicBackwardSubstitution, Test1)
{
    math::DynamicMatrixd A = {
        {2.0, 1.0},
        {0.0, 1.0}
    };
    math::DynamicVectord b = {
        3.0, 1.0
    };
    math::DynamicVectord correct_answer = {
        1.0, 1.0
    };
    math::DynamicVectord my_answer = math::backward_substitution_solve(A, b);
}

TEST(BackwardSubstitution, Test1)
{
    math::StaticArrayd<2,2> A = {
        {2.0, 1.0},
        {0.0, 1.0}
    };
    math::StaticVectord<2> b = {
        3.0, 1.0
    };
    math::StaticVectord<2> correct_answer = {
        1.0, 1.0
    };
    math::StaticVectord<2> my_answer = math::backward_substitution_solve(A, b);
}

TEST(DynamicCholesky, Test1)
{
    math::DynamicMatrixd A = {
        {1.0, 0.0},
        {0.0, 4.0}
    };
    math::DynamicMatrixd U_correct = {
        {sqrt(A(0,0)), 0.0},
        {0.0, sqrt(A(1,1))}
    };
    math::DynamicVectord b = {
        1.0, 4.0
    };
    math::DynamicVectord x_correct = {
        b(0)/A(0,0), b(1)/A(1,1)
    };
    math::DynamicCholeskyDecomposition cholesky(A);
    ASSERT_TRUE(math::all_equal(U_correct, cholesky.cholesky));
    ASSERT_TRUE(math::all_equal(x_correct, math::solve(cholesky, b)));
}

TEST(Cholesky, Test1)
{
    math::StaticArrayd<2,2> A = {
        {1.0, 0.0},
        {0.0, 4.0}
    };
    math::StaticArrayd<2,2> U_correct = {
        {sqrt(A(0,0)), 0.0},
        {0.0, sqrt(A(1,1))}
    };
    math::StaticVectord<2> b = {
        1.0, 4.0
    };
    math::StaticVectord<2> x_correct = {
        b(0)/A(0,0), b(1)/A(1,1)
    };
    math::CholeskyDecomposition cholesky(A);
    ASSERT_TRUE(math::all_equal(U_correct, cholesky.cholesky));
    ASSERT_TRUE(math::all_equal(x_correct, math::solve(cholesky, b)));
}

TEST(DynamicLUDecomposition, Test1)
{
    math::DynamicMatrixd A = {
        {1.0, 1.0, 1.0},
        {1.0, 4.0, 2.0},
        {4.0, 7.0, 8.0}
    };

    math::DynamicVectord b = {
        1.0,
        3.0,
        9.0
    };

    math::DynamicLUDecomposition lu(A);
    ASSERT_TRUE(math::all_equal(A(lu.P), lu.L*lu.U));
    auto solution = math::solve(lu, b);
    ASSERT_TRUE(math::all_equal(A*solution, b));
}

TEST(LUDecomposition, Test1)
{
    math::StaticArrayd<3,3> A = {
        {1.0, 1.0, 1.0},
        {1.0, 4.0, 2.0},
        {4.0, 7.0, 8.0}
    };

    math::StaticVectord<3> b = {
        1.0,
        3.0,
        9.0
    };

    math::LUDecomposition lu(A);
    ASSERT_TRUE(math::all_equal(A(lu.P), lu.L*lu.U));
    auto solution = math::solve(lu, b);
    ASSERT_TRUE(math::all_equal(A*solution, b));
}

TEST(QRDecomposition, Static)
{
    auto A = math::Identity<double,3>();
    math::QRDecomposition qr(A);
    auto QR_ = qr.Q*qr.R;
    std::cout << math::to_str(qr.Q);
    std::cout << math::to_str(qr.R);
    std::cout << math::to_str(QR_);
    ASSERT_TRUE(math::all_equal(qr.Q*qr.R, A));
}

TEST(SwapElements, Integers)
{
    int a = 1;
    int b = 2;
    math::swap(a,b);
    ASSERT_EQ(a,2);
    ASSERT_EQ(b,1);
}

TEST(SwapElements, Vector)
{
    math::StaticVectori<2> x = {
        1, 2
    };
    math::swap(x(0), x(1));
    ASSERT_EQ(x(0), 2);
    ASSERT_EQ(x(1), 1);
}