#pragma once
#include "base.hpp"

#include <initializer_list>

namespace math
{

template <typename T, int NumDims>
requires(NumDims > 1)
class Array<T, false, NumDims>
{
    public:
        using SubArray = Array<T, false, NumDims-1>;

    private:
        int length_;
        SubArray* data_;

        void check_input(int index) const
        {
            if(index >= length_ || index < 0)
            {
                throw OutOfRange(index, length_);
            }
        }

    public:
        using InitializerList = std::initializer_list<typename SubArray::InitializerList>;

        Array()
        : length_(0) {}

        template <typename ... OtherDims>
        requires(sizeof...(OtherDims) == NumDims-1)
        Array(int _length, OtherDims... others)
        : length_(_length), data_(new SubArray[length_]) 
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index].allocate(others...);
            }
        }

        ~Array()
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
        }

        SubArray operator()(int index) const
        {
            check_input(index);
            return data_[index];
        }

        SubArray& operator()(int index)
        {
            check_input(index);
            return data_[index];
        }

        template <typename ... OtherIndices>
        requires(sizeof...(OtherIndices) > 0)
        auto operator()(int index, OtherIndices... others) const
        {
            check_input(index);
            return data_[index](others...);
        }

        template <typename ... OtherIndices>
        requires(sizeof...(OtherIndices) > 0)
        auto& operator()(int index, OtherIndices... others)
        {
            check_input(index);
            return data_[index](others...);
        }

        int length() const
        {
            return length_;
        }

        void fill(T value)
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index].fill(value);
            }
        }

        void fill(const InitializerList& values)
        {
            int index = 0;
            for(typename SubArray::InitializerList value : values)
            {
                data_[index].fill(value);
                ++index;
            }
        } 

        template <typename ... OtherLengths>
        requires(sizeof...(OtherLengths) == NumDims-1)
        void allocate(int _length, OtherLengths... others)
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
            data_ = new SubArray[_length];
            for(int index = 0; index < _length; ++index)
            {
                data_[index].allocate(others...);
            }
            length_ = _length;
        }
};

template <typename T>
class Array<T, false, 1>
{
    private:
        int length_;
        T* data_;

        void check_input(int index) const
        {
            if(index >= length_ || index < 0)
            {
                throw OutOfRange(index, length_);
            }
        }

    public:
        using InitializerList = std::initializer_list<T>;

        Array()
        : length_(0) {}

        Array(int _length)
        : length_(_length), data_(new T[length_]) {}

        void allocate(int _length)
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
            data_ = new T[_length];
            length_ = _length;
        }

        ~Array()
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
        }

        T operator()(int index) const
        {
            check_input(index);
            return data_[index];
        }

        T& operator()(int index)
        {
            check_input(index);
            return data_[index];
        }

        int length() const
        {
            return length_;
        }

        void fill(const InitializerList& values)
        {
            int index = 0;
            for(T value : values)
            {
                data_[index] = value;
                ++index;
            }
        }

        void fill(T value)
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index] = value;
            }
        }
};

template <typename T, int NumDims>
using DynamicArray = Array<T, false, NumDims>;

template <int NumDims>
using DynamicArrayi = DynamicArray<int, NumDims>;

template <int NumDims>
using DynamicArrayf = DynamicArray<float, NumDims>;

template <int NumDims>
using DynamicArrayd = DynamicArray<double, NumDims>;

template <typename T>
using DynamicVector = DynamicArray<T, 1>;

using DynamicVectori = DynamicVector<int>;

using DynamicVectorf = DynamicVector<float>;

using DynamicVectord = DynamicVector<double>;

template <typename T>
DynamicVector<T> empty_like(const DynamicVector<T>& vector)
{
    DynamicVector<T> empty_vector(vector.length());
    return empty_vector;
}

template <typename T, int NumDims>
requires(NumDims > 1)
DynamicArray<T, NumDims> empty_like(const DynamicArray<T, NumDims>& array)
{
    DynamicArray<T, NumDims> empty_array(array.length());
    for(int index = 0; index < empty_array.length(); ++index)
    {
        empty_array(index) = empty_like(array(index));
    }
    return empty_array;
}
    
} // namespace math
