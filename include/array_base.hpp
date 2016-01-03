#pragma once

#include <cassert>

#include "non_member_functions.hpp"

// TODO:
//template<typename Array>
//T* data(Array& array);

template<typename Array>
std::array<size_t, 1> extents(const Array& a) { return std::array<size_t, 1>{a.size()}; }

template<typename T, size_t D>
struct array_base
{
	using value_type		= T;
	using reference			= value_type&;
	using const_reference	= const reference;
	using pointer			= value_type*;
	using const_pointer		= const pointer;
	using iterator			= pointer;
	using const_iterator	= const_pointer;
	using size_type			= std::size_t;
	using difference_type	= std::ptrdiff_t;
	
	static constexpr size_t RANK = D;
	static constexpr size_t rank() { return D; }

	template<typename Array>
	static typename Array::reference get_element(Array& a, size_t i0)
	{
		static_assert(a.rank() == 1, "Wrong dimensionality of the index");
		assert(i0 < a.extent0());
		return a[i0];
	}

	template<typename Array>
	static typename Array::const_reference get_element(const Array& a, size_t i0)
	{
		static_assert(a.rank() == 1, "Wrong dimensionality of the index");
		assert(i0 < a.extent0());
		return a[i0];
	}

	template<typename Array>
	static typename Array::reference get_element(Array& a, size_t i0, size_t i1)
	{
		static_assert(a.rank() == 2, "Wrong dimensionality of the index");
		assert(i0 < a.extent0());
		assert(i1 < a.extent1());
		return a[i0 + a.extent0() * i1];
	}

	template<typename Array>
	static typename Array::const_reference get_element(const Array& a, size_t i0, size_t i1)
	{
		static_assert(a.rank() == 2, "Wrong dimensionality of the index");
		assert(i0 < a.extent0());
		assert(i1 < a.extent1());
		return a[i0 + a.extent0() * i1];
	}

	template<typename Array>
	static typename Array::reference get_element(Array& a, size_t i0, size_t i1, size_t i2)
	{
		static_assert(a.rank() == 3, "Wrong dimensionality of the index");
		assert(i0 < a.extent0());
		assert(i1 < a.extent1());
		assert(i2 < a.extent2());
		return a[i0 + a.extent0() * (i1 + a.extent1() * i2)];
		//return data_[i0 + extent0() * i1 + extent0() * extent1() * i2];
	}

	template<typename Array>
	static typename Array::const_reference get_element(const Array& a, size_t i0, size_t i1, size_t i2)
	{
		static_assert(a.rank() == 3, "Wrong dimensionality of the index");
		assert(i0 < .extent0());
		assert(i1 < .extent1());
		assert(i2 < .extent2());
		return a[i0 + a.extent0() * (i1 + a.extent1() * i2)];
		//return data_[i0 + extent0() * i1 + extent0() * extent1() * i2];
	}

	//template<typename Array, typename... Indices>
	//static typename Array::const_reference get_element(const Array& a, size_t index, Indices... indices)
	//{
	//	return a[offset<Array, a.rank(), Indices...>(a, indices...)];
	//	//return data_[i0 + extent0() * i1 + extent0() * extent1() * i2];
	//}

	//template<typename Array, size_t dimension, typename... Indices>
	//static size_t offset(const Array& a, size_t index, Indices... indices)
	//{
	//	static_assert(sizeof...(indices) <= a.rank());
	//	return index + a.extent<dimension>() * offset<Array, dimension - 1, Indices>(indices...);
	//	// Kan inte kalla på offset här.
	//}

	template<typename Array, size_t dimension, typename... Indices>
	static size_t offset(const Array& a, Indices... indices)
	{
		return index;
	}

	template<typename Array, typename... Indices>
	static typename Array::const_reference get_element(const Array& a, Indices... indices)
	{
		return a[offset<Array, a.rank(), Indices...>(a, indices...)];
		//return data_[i0 + extent0() * i1 + extent0() * extent1() * i2];
	}

	template<typename Array, size_t dimension>
	static size_t product_size(const Array& a)
	{
		size_t product = 1;
		for (size_t i = 0; i < dimension; ++i)
		{
			product *= a.size<dimension>();
		}
		return product;
	}
};
