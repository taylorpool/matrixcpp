#pragma once

#include "base.hpp"
#include "dynamic.hpp"
#include <cmath>

namespace math
{

template <typename T, bool IsStatic, int ... Shape>
Array<bool, IsStatic, Shape ...> operator==(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    Array<bool, IsStatic, Shape ... > result = empty_like<T, bool>(left);
    for(int index = 0; index < result.length(); ++index)
    {
        result(index) = (left(index) == right(index));
    }
    return result;
}

template <bool IsStatic, int ... Shape>
Array<bool, IsStatic, Shape ...> operator!(const Array<bool, IsStatic, Shape ...>& array)
{
    Array<bool, IsStatic, Shape ... > result = empty_like(array);
    for(int index = 0; index < result.length(); ++index)
    {
        result(index) = !array(index);
    }
    return result;
}

template <typename T, bool IsStatic, int ... Shape>
Array<bool, IsStatic, Shape ...> operator!=(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    return !(left==right);
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape ...> operator-(const Array<T, IsStatic, Shape ...>& array)
{
    auto negative_array = empty_like(array);
    for(int index = 0; index < negative_array.length(); ++index)
    {
        negative_array(index) = -array(index);
    }
    return negative_array;
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape ...> operator+(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    auto summed = empty_like(left);
    for(int index = 0; index < summed.length(); ++index)
    {
        summed(index) = left(index) + right(index);
    }
    return summed;
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape ...> operator-(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    auto summed = empty_like(left);
    for(int index = 0; index < summed.length(); ++index)
    {
        summed(index) = left(index) - right(index);
    }
    return summed;
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape ...> operator/(const Array<T, IsStatic, Shape ...>& array, T divisor)
{
    auto divided = empty_like(array);
    for(int index = 0; index < divided.length(); ++index)
    {
        divided(index) = array(index)/divisor;
    }
    return divided;
}

template <typename T, bool IsStatic, int ... Shape>
Array<T, IsStatic, Shape ...> operator/=(Array<T, IsStatic, Shape ...>& array, T divisor)
{
    for(int index = 0; index < array.length(); ++index)
    {
        array(index) /= divisor;
    }
    return array;
}

template <typename T, int N>
T sum(const StaticVector<T,N>& vector)
{
    T summation = vector(0);
    for(int index = 1; index < N; ++index)
    {
        summation += vector(index);
    }
    return summation;
}

}