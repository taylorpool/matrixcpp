#pragma once
#include "base.hpp"

#include <initializer_list>

namespace math
{

class MismatchedLength: public std::exception
{
    private:
        int left_length_;
        int right_length_;

    public:
        MismatchedLength(int left_length, int right_length)
        : left_length_(left_length), right_length_(right_length) {}

        ~MismatchedLength() override {};

        const char* what() const noexcept override
        {
            return "mismatched lengths";
        }
};

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

        void check_length_matches(const Array& array) const
        {
            if(length_ != array.length())
            {
                throw MismatchedLength(length_, array.length());
            }
        }

    public:
        using InitializerList = std::initializer_list<typename SubArray::InitializerList>;

        Array()
        : length_(0) {}

        template <typename ... OtherDims>
        requires(sizeof...(OtherDims) == (NumDims-1))
        Array(int _length, OtherDims... others)
        : length_(_length), data_(new SubArray[length_]) 
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index].allocate(others...);
            }
        }

        Array(const Array& array)
        : length_(array.length()), data_(new SubArray[length_])
        {
            for(int index = 0; index < length_; ++index)
            {
                data_[index].fill(array(index));
            }
        }

        ~Array()
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
        }

        void fill(const Array& array)
        {
            if(length_ == 0)
            {
                allocate(array.length());
            }
            else if(length_ != array.length())
            {
                throw MismatchedLength(length_, array.length());
            }
            for(int index = 0; index < length_; ++index)
            {
                data_[index].fill(array(index));
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

        void allocate(int _length)
        {
            if(length_ > 0)
            {
                delete [] data_;
            }
            data_ = new SubArray[_length];
            length_ = _length;
        }

        template <typename ... OtherLengths>
        requires(sizeof...(OtherLengths) == (NumDims-1))
        void allocate(int _length, OtherLengths... others)
        {
            allocate(_length);
            for(int index = 0; index < length_; ++index)
            {
                data_[index].allocate(others...);
            }
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

        void check_length_matches(const Array& array) const
        {
            if(length_ != array.length())
            {
                throw MismatchedLength(length_, array.length());
            }
        }

    public:
        using InitializerList = std::initializer_list<T>;

        Array()
        : length_(0) {}

        Array(int _length)
        : length_(_length), data_(new T[length_]) {}

        Array(const Array& array)
        : length_(array.length()), data_(new T[length_])
        {
            fill(array);
        }

        Array(const InitializerList& values)
        : length_(values.size()), data_(new T[length_])
        {
            int index = 0;
            for(T value : values)
            {
                data_[index] = value;
                ++index;
            }
        }

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

        void fill(const Array& vector)
        {
            if(length_ == 0)
            {
                allocate(vector.length());
            }
            check_length_matches(vector);
            for(int index = 0; index < length_; ++index)
            {
                data_[index] = vector(index);
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

template <typename T>
bool all_equal(const DynamicVector<T>& left, const DynamicVector<T>& right)
{
    if(left.length() != right.length())
    {
        throw MismatchedLength(left.length(), right.length());
    }

    for(int index = 0; index < left.length(); ++index)
    {
        if(left(index) != right(index))
        {
            return false;
        }
    }
    return true;
}

template <typename T, int NumDims>
requires(NumDims > 1)
bool all_equal(const DynamicArray<T, NumDims>& left, const DynamicArray<T, NumDims>& right)
{
    if(left.length()!=right.length())
    {
        throw MismatchedLength(left.length(), right.length());
    }

    for(int index = 0; index < left.length(); ++index)
    {
        if(!all_equal(left(index), right(index)))
        {
            return false;
        }
    } 
    return true;
}
    
} // namespace math
