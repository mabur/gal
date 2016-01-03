#pragma once

#include <algorithm>
#include <array>

#include "array_base.hpp"

template<size_t size, size_t... sizes>
struct total_size
{
	static constexpr size_t value = size * total_size<sizes...>::value;
};

template<size_t size>
struct total_size<size>
{
	static constexpr size_t value = size;
};

template<size_t index, size_t first_size, size_t... sizes>
struct get_size
{
	static constexpr size_t value = get_size<index - 1, sizes...>::value;
};

template<size_t first_size, size_t...sizes>
struct get_size<0, first_size, sizes...>
{
	static constexpr size_t value = first_size;
};

template<typename T, size_t... extents>
class array_base_static : public array_base<T, sizeof...(extents)>
{
public:
	using Extents = std::array<size_t, RANK>;

	static constexpr size_t SIZE = total_size<extents...>::value;

	static constexpr size_t size() { return SIZE; };

	static constexpr size_t extent0() { return get_size<0, extents...>::value; }
	static constexpr size_t extent1() { return get_size<1, extents...>::value; }
	static constexpr size_t extent2() { return get_size<2, extents...>::value; }
	static constexpr size_t extent3() { return get_size<3, extents...>::value; }

	template<size_t dimension>
	static constexpr size_t extent()
	{
		return get_size<dimension, extents...>::value;
	}

	static constexpr Extents extents()
	{
		return { extents... };
	}
};
