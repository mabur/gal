#pragma once

#include <array>
#include <cstddef>

#include "non_member_functions.hpp"

/**
\brief The base class that all arrays derive from.
Contains some type aliases, and the definition of rank.
*/
template<typename T, size_t RANK>
struct array_base
{
	using value_type		= T;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= T*;
	using const_pointer		= const T*;
	using iterator			= T*;
	using const_iterator	= const T*;
	using size_type			= size_t;
	using difference_type	= ptrdiff_t;

    using extents_type      = std::array<size_t, RANK>;

	static constexpr size_t rank() { return RANK; }
};
