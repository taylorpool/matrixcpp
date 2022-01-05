#include "matrix/decompositions.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

TEST(ForwardSubstitution, Test1)
{
    math::Arrayd<2,2> A = {
        {1.0, 0.0},
        {2.0, 1.0}
    };
    math::Arrayd<2> b = {
        1.0, 4.0
    };
    math::Vectord<2> correct_answer = {
        1.0, 2.0
    };
    auto my_answer = math::forward_substitution_solve(A, b);
}

TEST(BackwardSubstitution, Test1)
{
    math::Arrayd<2,2> A = {
        {2.0, 1.0},
        {0.0, 1.0}
    };
    math::Vectord<2> b = {
        3.0, 1.0
    };
    math::Vectord<2> correct_answer = {
        1.0, 1.0
    };
    math::Vectord<2> my_answer = math::backward_substitution_solve(A, b);
}

TEST(Cholesky, Test1)
{
    math::Arrayd<2,2> A = {
        {1.0, 0.0},
        {0.0, 4.0}
    };
    math::Arrayd<2,2> U_correct = {
        {sqrt(A(0,0)), 0.0},
        {0.0, sqrt(A(1,1))}
    };
    math::Vectord<2> b = {
        1.0, 4.0
    };
    math::Vectord<2> x_correct = {
        b(0)/A(0,0), b(1)/A(1,1)
    };
    math::CholeskyDecomposition cholesky(A);
    ASSERT_EQ(U_correct, cholesky.cholesky);
    ASSERT_EQ(x_correct, math::solve(cholesky, b));
}

TEST(LUDecomposition, Test1)
{
    math::Arrayd<3,3> A = {
        {1.0, 1.0, 1.0},
        {1.0, 4.0, 2.0},
        {4.0, 7.0, 8.0}
    };

    math::Vectord<3> b = {
        1.0,
        3.0,
        9.0
    };

    math::LUDecomposition lu(A);
    ASSERT_EQ(A(lu.P), lu.L*lu.U);
    auto solution = math::solve(lu, b);
    ASSERT_EQ(A*solution, b);
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
    math::Vectori<2> x = {
        1, 2
    };
    math::swap(x(0), x(1));
    ASSERT_EQ(x(0), 2);
    ASSERT_EQ(x(1), 1);
}