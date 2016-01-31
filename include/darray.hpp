#pragma once

#include <algorithm>
#include <valarray>

#include "array_base_dynamic.hpp"

/**
\brief Dynamic array.
*/
template<typename T, size_t RANK = 1>
class darray : public array_base_dynamic<T, RANK>
{
public:

    using Extents = typename array_base<T, RANK>::Extents;

	darray() = default;
	
	explicit darray(const Extents& extents)
		: array_base_dynamic<T, RANK>(extents)
		, data_(product(extents))
	{}

	darray(const Extents& extents, const T& value)
		: array_base_dynamic<T, RANK>(extents)
		, data_(value, product(extents))
	{}

	darray(const Extents& extents, const T* data_begin)
		: array_base_dynamic<T, RANK>(extents)
		, data_(product(extents))
	{
		std::copy(data_begin, data_begin + size(), std::begin(data_));                
	}

	explicit darray(size_t size)
		: array_base_dynamic<T, RANK>({size})
		, data_(size)
	{
		static_assert(RANK == 1, "Wrong rank");
	}
	
	explicit darray(size_t size, const T& value)//, typename std::enable_if<D==1, T>::type* = nullptr)
		: array_base_dynamic<T, RANK>({size})
		, data_(value, size)
	{
		static_assert(RANK == 1, "Wrong rank");
	}
	
	darray(size_t size, const T* data_begin)
		: array_base_dynamic<T, RANK>({size})
		, data_(size)
	{
		static_assert(RANK == 1, "Wrong rank");
		std::copy(data_begin, data_begin + size, std::begin(data_));
	}

	template<typename Array>
	explicit darray(const Array& array, typename std::is_same<T, typename Array::value_type>::type* = nullptr)
		: array_base_dynamic<T, RANK>(::extents(array))
		, data_(array.size())
	{
		std::copy(std::begin(array), std::end(array), std::begin(data_));
	}

    size_t size() const { return data_.size(); };
	
	T*       begin()       {return std::begin(data_);};
	const T* begin() const {return std::begin(data_);};

	T*       end()         {return std::end(data_);};
	const T* end()   const {return std::end(data_);};

	T*       data()        {return std::begin(data_);};
	const T* data()  const {return std::begin(data_);};

	T& operator[](size_t i)
	{
		assert(i < size());
		return data_[i];
	}

	const T& operator[](size_t i) const
	{
		assert(i < size());
		return data_[i];
	}

	T& operator()(size_t i0)                       { return data_[i0]; }
	T& operator()(size_t i0, size_t i1)            { return data_[i0 + this->extent0() * i1]; }
    T& operator()(size_t i0, size_t i1, size_t i2) { return data_[i0 + this->extent0() * (i1 + this->extent1() * i2)]; }

	const T& operator()(size_t i0)                       const { return data_[i0]; }
	const T& operator()(size_t i0, size_t i1)            const { return data_[i0 + this->extent0() * i1]; }
    const T& operator()(size_t i0, size_t i1, size_t i2) const { return data_[i0 + this->extent0() * (i1 + this->extent1() * i2)]; }

private:
	std::valarray<T> data_;
};

template<typename T, size_t D> T*        data(      darray<T, D>& a) { return a.data(); }
template<typename T, size_t D> const T*  data(const darray<T, D>& a) { return a.data(); }
template<typename T, size_t D> T*       begin(      darray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> const T* begin(const darray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> T*         end(      darray<T, D>& a) { return a.end(); }
template<typename T, size_t D> const T*   end(const darray<T, D>& a) { return a.end(); }
template<typename T, size_t D> size_t    size(const darray<T, D>& a) { return a.size(); }
template<typename T, size_t D> std::array<size_t, D> extents(const darray<T, D>& a) { return a.extents(); }

template<typename T, size_t D> constexpr size_t rank(const darray<T, D>& a) { return a.rank(); }

