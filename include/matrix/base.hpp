#pragma once

#include <initializer_list>

namespace math
{

template <typename T, int ... Dims> class Matrix;

template <typename T, int Dim>
class Matrix<T, Dim>
{
    private:
        T data_[Dim];

    public:
        using InitializerList = std::initializer_list<T>;

        Matrix(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < Dim; ++i)
            {
                data_[i] = initial_value;
            }
        }

        Matrix(InitializerList values)
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
class Matrix<T, FirstDim, OtherDim...>
{
    private:
        Matrix<T, OtherDim...> data_[FirstDim];

    public:
        using InitializerList = std::initializer_list<typename Matrix<T, OtherDim...>::InitializerList>;

        Matrix(T initial_value = static_cast<T>(0))
        {
            for(int i = 0; i < FirstDim; ++i)
            {
                data_[i] = Matrix<T, OtherDim...>(initial_value);
            }
        }

        Matrix(InitializerList initializer_list)
        {
            int i = 0;
            for(auto iter = initializer_list.begin(); iter != initializer_list.end(); ++iter)
            {
                data_[i] = Matrix<T, OtherDim...>(*iter);
                ++i;
            }
        }

        Matrix<T, OtherDim...>& operator()(int index)
        {
            return data_[index];
        }

        Matrix<T, OtherDim...> operator()(int index) const
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
using Vector = Matrix<T, Size>;

template <int Size>
using Vectord = Vector<double, Size>;

template <int Size>
using Vectori = Vector<int, Size>;

template <int ... Shape>
using Matrixd = Matrix<double, Shape ... >;

template <int ... Shape>
using Matrixi = Matrix<int, Shape ... >;

template <typename T, int FirstDim, int ... Shape>
bool operator==(const Matrix<T, FirstDim, Shape...>& left, const Matrix<T, FirstDim, Shape...>& right)
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
bool operator!=(const Matrix<T, FirstDim, Shape...>& left, const Matrix<T, FirstDim, Shape...>& right)
{
    return false == (left == right);
}
}