#pragma once

#include <algorithm>
#include <array>
#include <initializer_list>

#include "array_base_static.hpp"

/**
\brief Static array.
*/
template<typename T, size_t... EXTENTS>
class sarray : public array_base_static<T, EXTENTS...>
{
public:

    static constexpr size_t SIZE = array_base_static<T, EXTENTS...>::size();
    using array_base_static<T, EXTENTS...>::size;
    using array_base_static<T, EXTENTS...>::extent;
    using array_base_static<T, EXTENTS...>::extent0;

	sarray() = default;

	//explicit sarray(const std::array<T, total_size<EXTENTS...>::value>& data)
	//	: data_(data)
	//{}

	explicit sarray(const std::initializer_list<T>& data)
	{
		assert(data.size() == data_.size());
		std::copy(data.begin(), data.end(), data_.begin());
	}

	explicit sarray(const T& value)
	{
		std::fill(std::begin(data_), std::end(data_), value);
	}

	explicit sarray(const T* data_begin)
	{
		std::copy(data_begin, data_begin + size(), std::begin(data_));
	}

	// TODO: fix.
	template<typename Array>
	explicit sarray(const Array& array,
		typename std::is_same<T, typename Array::value_type>::type* = nullptr)
	{
		assert(array.size() == size());
		std::copy(std::begin(array), std::end(array), std::begin(data_));
	}

	T*       begin()       {return data();};
	const T* begin() const {return data();};

	T*       end()         {return data() + size();};
	const T* end()   const {return data() + size();};

	T*       data()        {return data_.data();};
	const T* data()  const {return data_.data();};

	T&       operator[](size_t i)       { return data_[i]; }
	const T& operator[](size_t i) const { return data_[i]; }

	T& operator()(size_t i0)                       { return data_[i0]; }
	T& operator()(size_t i0, size_t i1)            { return data_[i0 + extent0() * i1]; }
    T& operator()(size_t i0, size_t i1, size_t i2) { return data_[i0 + extent<0>() * (i1 + extent<1>() * i2)]; }

	const T& operator()(size_t i0)                       const { return data_[i0]; }
	const T& operator()(size_t i0, size_t i1)            const { return data_[i0 + extent<0>() * i1]; }
    const T& operator()(size_t i0, size_t i1, size_t i2) const { return data_[i0 + extent<0>() * (i1 + extent<1>() * i2)]; }

private:

	std::array<T, SIZE> data_;
};

template<typename T, size_t... EXTENTS> T*        data(      sarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> const T*  data(const sarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> T*       begin(      sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(      sarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> const T*   end(const sarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> size_t    size(const sarray<T, EXTENTS...>& a) { return a.size(); }

template<typename T, size_t... EXTENTS> std::array<size_t, sizeof...(EXTENTS)> extents(const sarray<T, EXTENTS...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const sarray<T, W, H>& a) {return a.rank();}
