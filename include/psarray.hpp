#pragma once

#include "array_base_static.hpp"

/**
\brief Pointer to a static array.
*/
template<typename T, size_t... SIZES>
class psarray : public array_base_static<T, SIZES...>
{
public:
	psarray() : data_(nullptr) {}

    // TODO: fix.
	explicit psarray(T* data) : data_(data) {}

	// TODO: fix.
	template<typename Array>
	explicit psarray(Array& array,
		typename std::is_same<T, typename Array::value_type>::type* = nullptr)
		: data_(std::data(array))
	{
		assert(array.size() == size());
	}

	static constexpr size_t extent0() { return get_size<0, SIZES...>::value; }
	static constexpr size_t extent1() { return get_size<1, SIZES...>::value; }
	static constexpr size_t extent2() { return get_size<2, SIZES...>::value; }
	static constexpr size_t extent3() { return get_size<3, SIZES...>::value; }

	static constexpr std::array<size_t, RANK> extents() { return std::array<size_t, RANK>{SIZES...}; }

	inline T* begin()    const { return data_; }
	inline T* end()      const { return data_ + size(); }
	inline T* data()     const { return data_; }

	inline T& operator[](size_t i) const
	{
		assert(i < size());
		return data_[i];
	}

	T& operator()(size_t i0) { return get_element(*this, i0); }
	T& operator()(size_t i0, size_t i1) { return get_element(*this, i0, i1); }
	T& operator()(size_t i0, size_t i1, size_t i2) { return get_element(*this, i0, i1, i2); }

	const T& operator()(size_t i0)                       const { return get_element(*this, i0); }
	const T& operator()(size_t i0, size_t i1)            const { return get_element(*this, i0, i1); }
	const T& operator()(size_t i0, size_t i1, size_t i2) const { return get_element(*this, i0, i1, i2); }

private:
	T* data_;
};

template<typename T, size_t... SIZES> T*        data(psarray<T, SIZES...>& a) { return a.data(); }
template<typename T, size_t... SIZES> const T*  data(const psarray<T, SIZES...>& a) { return a.data(); }
template<typename T, size_t... SIZES> T*       begin(psarray<T, SIZES...>& a) { return a.begin(); }
template<typename T, size_t... SIZES> const T* begin(const psarray<T, SIZES...>& a) { return a.begin(); }
template<typename T, size_t... SIZES> T*         end(psarray<T, SIZES...>& a) { return a.end(); }
template<typename T, size_t... SIZES> const T*   end(const psarray<T, SIZES...>& a) { return a.end(); }
template<typename T, size_t... SIZES> size_t    size(const psarray<T, SIZES...>& a) { return a.size(); }

template<typename T, size_t... SIZES> std::array<size_t, sizeof...(SIZES)> extents(const psarray<T, SIZES...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const psarray<T, W, H>& a) { return a.rank(); }
