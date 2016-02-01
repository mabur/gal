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

/**
\brief The base class that all static arrays derive from,
i.e. arrays with size known at compile-time. Defines size and extents for such arrays.
*/
template<typename T, size_t... EXTENTS>
class array_base_static : public array_base<T, sizeof...(EXTENTS)>
{
public:
    using typename array_base<T, sizeof...(EXTENTS)>::extents_type;

	static constexpr size_t size() { return total_size<EXTENTS...>::value; };

    static constexpr extents_type extents() { return{ EXTENTS... }; }

    template<size_t DIMENSION>
    static constexpr size_t extent()
    {
        return get_size<DIMENSION, EXTENTS...>::value;
    }

	static constexpr size_t extent0() { return extent<0>(); }
	static constexpr size_t extent1() { return extent<1>(); }
	static constexpr size_t extent2() { return extent<2>(); }
	static constexpr size_t extent3() { return extent<3>(); }
};
