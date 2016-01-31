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

template<typename T, size_t... EXTENTS>
class array_base_static : public array_base<T, sizeof...(EXTENTS)>
{
public:
    static constexpr size_t rank() { return sizeof...(EXTENTS); }

	static constexpr size_t SIZE = total_size<EXTENTS...>::value;

    using Extents = std::array<size_t, sizeof...(EXTENTS)>;

	static constexpr size_t size() { return SIZE; };

	static constexpr size_t extent0() { return get_size<0, EXTENTS...>::value; }
	static constexpr size_t extent1() { return get_size<1, EXTENTS...>::value; }
	static constexpr size_t extent2() { return get_size<2, EXTENTS...>::value; }
	static constexpr size_t extent3() { return get_size<3, EXTENTS...>::value; }

	template<size_t dimension>
	static constexpr size_t extent()
	{
		return get_size<dimension, EXTENTS...>::value;
	}

	static constexpr Extents extents()
	{
		return { EXTENTS... };
	}
};
