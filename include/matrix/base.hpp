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

        Array() {};

        Array(T initial_value)
        {
            fill(initial_value);
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
        Array<T, Size> operator()(const Array<int, Size>& indices) const
        {
            Array<T, Size> indexed;
            for(int index = 0; index < Size; ++index)
            {
                indexed(index) = data_[indices(index)];
            }
            return indexed;
        }
};

template <typename T, int FirstDim, int ... OtherDim>
class Array<T, FirstDim, OtherDim...>
{
    private:
        Array<T, OtherDim...> data_[FirstDim];

    public:
        using InitializerList = std::initializer_list<typename Array<T, OtherDim...>::InitializerList>;

        Array() {};

        Array(T initial_value)
        {
            fill(initial_value);
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

        void fill(T value)
        {
            for(int i = 0; i < FirstDim; ++i)
            {
                data_[i].fill(value);
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

        template <int Size>
        Array<T, Size, OtherDim...> operator()(const Array<int, Size>& indices) const
        {
            Array<T, Size, OtherDim...> indexed;
            for(int index = 0; index < Size; ++index)
            {
                indexed(index) = data_[indices(index)];
            }
            return indexed;
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