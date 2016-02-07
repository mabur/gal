#pragma once

#include <cassert>

#include "array_base_static.hpp"

/**
\brief Pointer to a static array.
*/
template<typename T, size_t... EXTENTS>
class psarray : public array_base_static<T, EXTENTS...>
{
public:

    using array_base_static<T, EXTENTS...>::size;
    using array_base_static<T, EXTENTS...>::extent;

	psarray() : data_(nullptr) {}

    psarray(const psarray<T, EXTENTS...>&) = default;

    psarray<T, EXTENTS...>& operator=(const psarray<T, EXTENTS...>&) = default;

	explicit psarray(T* data) : data_(data) {}

    template<typename S>
    explicit psarray(const psarray<S, EXTENTS...>& array)
        : data_(array.data())
    {}

	template<typename Array, typename Array::value_type* = nullptr>
	explicit psarray(Array& array)
		: data_(::data(array))
	{
		assert(array.size() == size());
	}

    template<typename Array, typename Array::value_type* = nullptr>
    explicit psarray(const Array& array)
        : data_(::data(array))
    {
        assert(array.size() == size());
    }

	inline T* begin() const { return data_; }
	inline T* end()   const { return data_ + size(); }
	inline T* data()  const { return data_; }

	inline T& operator[](size_t i) const
	{
		assert(i < size());
		return data_[i];
	}

    template<typename ... INDICES>
    T& operator()(INDICES ... indices) { return details::index(*this, indices...); }

    template<typename ... INDICES>
    const T& operator()(INDICES ... indices) const { return details::index(*this, indices...); }

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

template<typename T, size_t... EXTENTS> extents_t<sizeof...(EXTENTS)> extents(const psarray<T, EXTENTS...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const psarray<T, W, H>& a) { return a.rank(); }
