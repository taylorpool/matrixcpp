#include "matrix/decompositions.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

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
    auto U = math::cholesky(A);
    ASSERT_EQ(U_correct, U);
    ASSERT_EQ(x_correct, math::cholesky_solve(U, b));
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
    math::LUSolution solution(lu, b);
    math::Vectord<3> Ax = A*solution.solution;
    math::Vectord<3> Ly = lu.L*solution.y;
    math::Vectord<3> Pb = b(lu.P);
    ASSERT_EQ(Ly, Pb);
    math::Vectord<3> Ux = lu.U*solution.solution;
    ASSERT_EQ(A*solution.solution, b);
}