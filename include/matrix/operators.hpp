#pragma once

#include "base.hpp"

namespace math
{

template <typename T, bool IsStatic, int ... Shape>
bool operator==(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    for(int index = 0; index < left.length(); ++index)
    {
        if(left(index) != right(index))
        {
            return false;
        }
    }
    return true;
}

template <typename T, bool IsStatic, int ... Shape>
bool operator!=(const Array<T, IsStatic, Shape ...>& left, const Array<T, IsStatic, Shape ...>& right)
{
    return false == (left == right);
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

}