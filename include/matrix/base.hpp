#pragma once

namespace math
{

template <typename T, bool IsStatic, int ... Dims> class Array;

template <typename T, bool IsStatic, int Size>
using Vector = Array<T, IsStatic, Size>;

template <bool IsStatic, int Size>
using Vectord = Vector<double, IsStatic, Size>;

template <bool IsStatic, int Size>
using Vectori = Vector<int, IsStatic, Size>;

template <bool IsStatic, int ... Shape>
using Arrayd = Array<double, IsStatic, Shape ... >;

template <bool IsStatic, int ... Shape>
using Arrayi = Array<int, IsStatic, Shape ... >;

}