#pragma once

#include <cassert>

#include "non_member_functions.hpp"

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
	using size_type			= std::size_t;
	using difference_type	= std::ptrdiff_t;

    using extents_type      = std::array<size_t, RANK>;

	static constexpr size_t rank() { return RANK; }
};
