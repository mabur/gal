#pragma once

#include <algorithm>
#include <array>
#include <initializer_list>

#include "array_base_static.hpp"

/**
\brief Static array.
*/
template<typename T, size_t... SIZES>
class sarray : public array_base_static<T, SIZES...>
{
public:
	sarray() = default;

	//explicit sarray(const std::array<T, total_size<SIZES...>::value>& data)
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

	static constexpr size_t extent0() { return get_size<0, SIZES...>::value; }
	static constexpr size_t extent1() { return get_size<1, SIZES...>::value; }
	static constexpr size_t extent2() { return get_size<2, SIZES...>::value; }
	static constexpr size_t extent3() { return get_size<3, SIZES...>::value; }

	static constexpr std::array<size_t, RANK> extents() { return std::array<size_t, RANK>{SIZES...}; }

	T*       begin()       {return data();};
	const T* begin() const {return data();};

	T*       end()         {return data() + size();};
	const T* end()   const {return data() + size();};

	T*       data()        {return data_.data();};
	const T* data()  const {return data_.data();};

	T&       operator[](size_t i)       { return data_[i]; }
	const T& operator[](size_t i) const { return data_[i]; }

	T& operator()(size_t i0)                       { return get_element(*this, i0); }
	T& operator()(size_t i0, size_t i1)            { return get_element(*this, i0, i1); }
	T& operator()(size_t i0, size_t i1, size_t i2) { return get_element(*this, i0, i1, i2); }

	const T& operator()(size_t i0)                       const { return get_element(*this, i0); }
	const T& operator()(size_t i0, size_t i1)            const { return get_element(*this, i0, i1); }
	const T& operator()(size_t i0, size_t i1, size_t i2) const { return get_element(*this, i0, i1, i2); }

private:

	std::array<T, SIZE> data_;
};

template<typename T, size_t... SIZES> T*        data(      sarray<T, SIZES...>& a) { return a.data(); }
template<typename T, size_t... SIZES> const T*  data(const sarray<T, SIZES...>& a) { return a.data(); }
template<typename T, size_t... SIZES> T*       begin(      sarray<T, SIZES...>& a) { return a.begin(); }
template<typename T, size_t... SIZES> const T* begin(const sarray<T, SIZES...>& a) { return a.begin(); }
template<typename T, size_t... SIZES> T*         end(      sarray<T, SIZES...>& a) { return a.end(); }
template<typename T, size_t... SIZES> const T*   end(const sarray<T, SIZES...>& a) { return a.end(); }
template<typename T, size_t... SIZES> size_t    size(const sarray<T, SIZES...>& a) { return a.size(); }

template<typename T, size_t... SIZES> std::array<size_t, sizeof...(SIZES)> extents(const sarray<T, SIZES...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const sarray<T, W, H>& a) {return a.rank();}
