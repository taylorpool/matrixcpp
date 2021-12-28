#pragma once

#include <initializer_list>

namespace math
{

template <typename T, int ... Dims> class Array;

template <typename T, int Dim>
class Array<T, Dim>
{
    private:
        T data_[Dim];

    public:
        using InitializerList = std::initializer_list<T>;

        Array(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < Dim; ++i)
            {
                data_[i] = initial_value;
            }
        }

        Array(InitializerList values)
        {
            auto iter = values.begin();
            for(int index = 0; index < values.size(); ++index)
            {
                data_[index] = *iter;
                ++iter;
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
};

template <typename T, int FirstDim, int ... OtherDim>
class Array<T, FirstDim, OtherDim...>
{
    private:
        Array<T, OtherDim...> data_[FirstDim];

    public:
        using InitializerList = std::initializer_list<typename Array<T, OtherDim...>::InitializerList>;

        Array(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < FirstDim; ++i)
            {
                data_[i] = Array<T, OtherDim...>(initial_value);
            }
        }

        Array(InitializerList initializer_list)
        {
            int i = 0;
            for(auto iter = initializer_list.begin(); iter != initializer_list.end(); ++iter)
            {
                data_[i] = Array<T, OtherDim...>(*iter);
                ++i;
            }
        }

        Array<T, OtherDim...>& operator()(int index)
        {
            return data_[index];
        }

        Array<T, OtherDim...> operator()(int index) const
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
};

template <typename T, int Size>
using Vector = Array<T, Size>;

template <int Size>
using Vectord = Vector<double, Size>;

template <int Size>
using Vectori = Vector<int, Size>;

template <int ... Shape>
using Arrayd = Array<double, Shape ... >;

template <int ... Shape>
using Arrayi = Array<int, Shape ... >;

template <typename T, int N>
Array<T, N, N> Identity()
{
    Array<T, N, N> matrix;
    T identity_element = static_cast<T>(1);
    for(int index = 0; index < N; ++index)
    {
        matrix(index, index) = identity_element;
    }
    return matrix;
}

template <int N>
Vectori<N> ARange()
{
    Vectori<N> range;
    for(int index = 0; index < N; ++ index)
    {
        range(index) = index;
    }
    return range;
}

template <typename T, int FirstDim, int ... Shape>
bool operator==(const Array<T, FirstDim, Shape...>& left, const Array<T, FirstDim, Shape...>& right)
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
bool operator!=(const Array<T, FirstDim, Shape...>& left, const Array<T, FirstDim, Shape...>& right)
{
    return false == (left == right);
}
}