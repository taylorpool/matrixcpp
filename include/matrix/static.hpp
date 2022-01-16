#pragma once

#include "base.hpp"

#include <initializer_list>

namespace math
{

template <typename T, int Dim>
class Array<T, true, Dim>
{
    private:
        T data_[Dim];

    public:
        using InitializerList = std::initializer_list<T>;

        Array<T, true, Dim>() {};

        Array<T, true, Dim>(T initial_value)
        {
            fill(initial_value);
        }

        Array<T, true, Dim>(InitializerList values)
        {
            auto iter = values.begin();
            for(int index = 0; index < values.size(); ++index)
            {
                data_[index] = *iter;
                ++iter;
            }
        }

        void fill(T value)
        {
            for(int i = 0; i < Dim; ++i)
            {
                data_[i] = value;
            }
        }

        T& operator()(int index)
        {
            return data_[index];
        }

        T operator()(int index) const
        {
            return data_[index];
        }

        template <int Size>
        Array<T, true, Size> operator()(const Array<int, true, Size>& indices) const
        {
            Array<T, true, Size> indexed;
            for(int index = 0; index < Size; ++index)
            {
                indexed(index) = data_[indices(index)];
            }
            return indexed;
        }
};

template <typename T, int FirstDim, int ... OtherDim>
class Array<T, true, FirstDim, OtherDim...>
{
    private:
        Array<T, true, OtherDim...> data_[FirstDim];

    public:
        using InitializerList = std::initializer_list<typename Array<T, true, OtherDim...>::InitializerList>;

        Array<T, true, FirstDim, OtherDim...>() {};

        Array<T, true, FirstDim, OtherDim...>(T initial_value)
        {
            fill(initial_value);
        }

        Array<T, true, FirstDim, OtherDim...>(InitializerList initializer_list)
        {
            int i = 0;
            for(auto iter = initializer_list.begin(); iter != initializer_list.end(); ++iter)
            {
                data_[i] = Array<T, true, OtherDim...>(*iter);
                ++i;
            }
        }

        void fill(T value)
        {
            for(int i = 0; i < FirstDim; ++i)
            {
                data_[i].fill(value);
            }
        }

        Array<T, true, OtherDim...>& operator()(int index)
        {
            return data_[index];
        }

        Array<T, true, OtherDim...> operator()(int index) const
        {
            return data_[index];
        }

        template <typename ... OtherIndices>
        auto operator()(int first, OtherIndices... others) const
        {
            return data_[first](others...);
        }

        template <typename ... OtherIndices>
        auto& operator()(int first, OtherIndices... others)
        {
            return data_[first](others...);
        }

        template <int Size>
        Array<T, true, Size, OtherDim...> operator()(const Array<int, true, Size>& indices) const
        {
            Array<T, true, Size, OtherDim...> indexed;
            for(int index = 0; index < Size; ++index)
            {
                indexed(index) = data_[indices(index)];
            }
            return indexed;
        }
};

template <typename T, int ... Shape>
using StaticArray = Array<T, true, Shape...>;

template <int ... Shape>
using StaticArrayi = StaticArray<int, Shape...>;

template <int ... Shape>
using StaticArrayf = StaticArray<float, Shape...>;

template <int ... Shape>
using StaticArrayd = StaticArray<double, Shape...>;

template <typename T, int Size>
using StaticVector = StaticArray<T, Size>;

template <int Size>
using StaticVectori = StaticVector<int, Size>;

template <int Size>
using StaticVectorf = StaticVector<float, Size>;

template <int Size>
using StaticVectord = StaticVector<double, Size>;

template <typename T, int N>
StaticArray<T, N, N> Identity()
{
    StaticArray<T, N, N> matrix;
    T identity_element = static_cast<T>(1);
    T zero_element = static_cast<T>(0);
    for(int row = 0; row < N; ++row)
    {
        for(int column = 0; column < N; ++column)
        {
            matrix(row,column) = (row==column ? identity_element : zero_element);
        }
    }
    return matrix;
}

template <int N>
Vectori<true, N> ARange()
{
    Vectori<true, N> range;
    for(int index = 0; index < N; ++ index)
    {
        range(index) = index;
    }
    return range;
}

template <typename T, int FirstDim, int ... Shape>
bool operator==(const StaticArray<T, FirstDim, Shape...>& left, const StaticArray<T, FirstDim, Shape...>& right)
{
    for(int index = 0; index < FirstDim; ++index)
    {
        if(left(index) != right(index))
        {
            return false;
        }
    }
    return true;
}

template <typename T, int FirstDim, int ... Shape>
bool operator!=(const StaticArray<T, FirstDim, Shape...>& left, const StaticArray<T, FirstDim, Shape...>& right)
{
    return false == (left == right);
}
}