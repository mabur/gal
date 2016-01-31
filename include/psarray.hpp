#pragma once

#include "array_base_static.hpp"

/**
\brief Pointer to a static array.
*/
template<typename T, size_t... EXTENTS>
class psarray : public array_base_static<T, EXTENTS...>
{
public:
    static const size_t RANK = sizeof...(EXTENTS);
    static const size_t SIZE = total_size<EXTENTS...>::value;

    static constexpr size_t size() { return SIZE; };
    static constexpr size_t rank() { return RANK; }


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

	static constexpr size_t extent0() { return get_size<0, EXTENTS...>::value; }
	static constexpr size_t extent1() { return get_size<1, EXTENTS...>::value; }
	static constexpr size_t extent2() { return get_size<2, EXTENTS...>::value; }
	static constexpr size_t extent3() { return get_size<3, EXTENTS...>::value; }

	static constexpr std::array<size_t, sizeof...(EXTENTS)> extents()
    {
        return std::array<size_t, rank()>{EXTENTS...};
    }

	inline T* begin()    const { return data_; }
	inline T* end()      const { return data_ + size(); }
	inline T* data()     const { return data_; }

	inline T& operator[](size_t i) const
	{
		assert(i < size());
		return data_[i];
	}

	T& operator()(size_t i0)                       { return data_[i0]; }
	T& operator()(size_t i0, size_t i1)            { return data_[i0 + extent0() * i1]; }
    T& operator()(size_t i0, size_t i1, size_t i2) { return data_[i0 + extent0() * (i1 + extent1() * i2)]; }

	const T& operator()(size_t i0)                       const { return data_[i0]; }
	const T& operator()(size_t i0, size_t i1)            const { return data_[i0 + extent0() * i1]; }
    const T& operator()(size_t i0, size_t i1, size_t i2) const { return data_[i0 + extent0() * (i1 + extent1() * i2)]; }

private:
	T* data_;
};

template<typename T, size_t... EXTENTS> T*        data(psarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> const T*  data(const psarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> T*       begin(psarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const psarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(psarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> const T*   end(const psarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> size_t    size(const psarray<T, EXTENTS...>& a) { return a.size(); }

template<typename T, size_t... EXTENTS> std::array<size_t, sizeof...(EXTENTS)> extents(const psarray<T, EXTENTS...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const psarray<T, W, H>& a) { return a.rank(); }
