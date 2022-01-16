#include "matrix/dynamic.hpp"
#include <gtest/gtest.h>

class DynamicVector: public ::testing::Test
{
    protected:
        int size = 2;
        math::dynamic::Vectori vectori;
        math::dynamic::Vectord vectord;
        math::dynamic::Vector<bool> vectorb;

        DynamicVector()
        : vectori(size), vectord(size),
          vectorb(size) {};
};

TEST_F(DynamicVector, Size2TypeInt)
{
    ASSERT_EQ(vectori.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeInt)
{
    int first_value = 1;
    vectori(0) = first_value;
    ASSERT_EQ(vectori(0), first_value);
}

TEST_F(DynamicVector, Size2TypeDouble)
{
    ASSERT_EQ(vectord.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeDouble)
{
    double first_value = 1.0;
    vectord(0) = first_value;
    ASSERT_EQ(vectord(0), first_value);
}

TEST_F(DynamicVector, Size2TypeBool)
{
    ASSERT_EQ(vectorb.size(), size);
}

TEST_F(DynamicVector, SetElementsTypeBool)
{
    bool first_value = false;
    vectorb(0) = first_value;
    ASSERT_EQ(vectorb(0), first_value);
}