#pragma once

#include "static.hpp"

namespace math
{
template <typename T, int FirstDim, int ... OtherDims>
Array<T, FirstDim, OtherDims...> operator-(const Array<T, FirstDim, OtherDims...>& array)
{
    Array<T, FirstDim, OtherDims...> negative_array;
    for(int index = 0; index < FirstDim; ++index)
    {
        negative_array(index) = -array(index);
    }
    return negative_array;
}

template <typename T, int FirstDim, int ... OtherDims>
Array<T, FirstDim, OtherDims...> operator+(const Array<T, FirstDim, OtherDims...>& left, const Array<T, FirstDim, OtherDims...>& right)
{
    Array<T, FirstDim, OtherDims...> summed;
    for(int index = 0; index < FirstDim; ++index)
    {
        summed(index) = left(index) + right(index);
    }
    return summed;
}

template <typename T, int FirstDim, int ... OtherDims>
Array<T, FirstDim, OtherDims...> operator-(const Array<T, FirstDim, OtherDims...>& left, const Array<T, FirstDim, OtherDims...>& right)
{
    return left + (-right);
}
}