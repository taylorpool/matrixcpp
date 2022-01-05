#pragma once

#include "base.hpp"

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
}