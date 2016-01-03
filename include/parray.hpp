// Copyright 2015 Volumental AB. CONFIDENTIAL. DO NOT REDISTRIBUTE.
#pragma once

#include <algorithm>
#include <array>
#include <cassert>

#include "array_base.hpp"
#include "array_base_dynamic.hpp"
#include "utilities.hpp"

// Forward declarations:
template<typename T, size_t D> class parray;
inline size_t product(const size_t* array, size_t size);

/**
* \brief parray<T, D> points to an array / random-access-container with
* D dimensions, where each element has type T.
*
* The default value is D=1. For images D=2 and for voxel volumes D=3.
*
* A single-dimensional parray<T, 1> can be created automatically from:
* * std::vector
* * std::array
* * std::valarray
* * Eigen::Matrix
*
* Note that parray does not own the object it points to. It is a light
* wrapper object that only points to an array owned by someone else.
* It can point to constant data by setting e.g. T = const float.
* It provides an abstract array interface via the member functions:
* * begin()
* * end()
* * data()
* * size()
*
* A user of parray can therefore have polymorphic behavior and deal with
* general arrays, without using templates or inheritance.
* parray can be used in range based for-loops.
*
* A multi-dimensional parray<T, D> can be used like this:
* \code
* size_t width  = 640;
* size_t height = 480;
* size_t depth  = 256;
* parray<float, 3> array(data, width, height, depth);
* for (auto& x : array)
* {
*     f(x);
* }
* for (size_t i = 0; i < array.size(); ++i)
* {
*     f(array[i]);
* }
* for (size_t z = 0; z < array.size(2); ++z)
* {
*     for (size_t y = 0; y < array.size(1); ++y)
*     {
*         for (size_t x = 0; x < array.size(0); ++x)
*         {
*             array(x, y, z) = f(x, y, z);
*         }
*     }
* }
* \endcode
*/
template<typename T, size_t D = 1>
class parray : public array_base_dynamic<T, D>
{
public:

    parray() : data_(nullptr), size_(0) {}

	parray(const std::array<size_t, D>& sizes, T* data)
		: array_base_dynamic(sizes)
		, data_(data)
		, size_(array_base_dynamic::size())
	{
		assert(data_ != nullptr || size_ == 0);
	}

    template<typename Array>
    parray(Array& array)
		: array_base_dynamic(::extents(array))
		, data_(array.data())
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0);
    }

    template<typename Array>
    parray(const Array& array)
		: array_base_dynamic(::extents(array))
		, data_(array.data())
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0);
    }

    inline T* begin()    const { return data_; }
    inline T* end()      const { return data_ + size_; }
    inline T* data()     const { return data_; }
    inline size_t size() const { return size_; }

    inline T& operator[](size_t i) const
    {
        assert(i < size());
        return data_[i];
    }

	T& operator()(size_t i0)                       { return get_element(*this, i0); }
	T& operator()(size_t i0, size_t i1)            { return get_element(*this, i0, i1); }
	T& operator()(size_t i0, size_t i1, size_t i2) { return get_element(*this, i0, i1, i2); }

	const T& operator()(size_t i0)                       const { return get_element(*this, i0); }
	const T& operator()(size_t i0, size_t i1)            const { return get_element(*this, i0, i1); }
	const T& operator()(size_t i0, size_t i1, size_t i2) const { return get_element(*this, i0, i1, i2); }

private:
    T* data_;
    size_t size_;
};

template<typename T, size_t D> T*        data(parray<T, D>& a)       { return a.data(); }
template<typename T, size_t D> const T*  data(const parray<T, D>& a) { return a.data(); }
template<typename T, size_t D> T*       begin(parray<T, D>& a)       { return a.begin(); }
template<typename T, size_t D> const T* begin(const parray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> T*         end(parray<T, D>& a)       { return a.end(); }
template<typename T, size_t D> const T*   end(const parray<T, D>& a) { return a.end(); }
template<typename T, size_t D> size_t    size(const parray<T, D>& a) { return a.size(); }

template<typename T, size_t D> constexpr size_t rank(const parray<T, D>& a) { return a.rank(); }

template<typename T, size_t D> std::array<size_t, D> extents(const parray<T, D>& a) { return a.extents(); }
