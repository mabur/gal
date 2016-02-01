#pragma once

#include <algorithm>
#include <array>

#include "array_base.hpp"
#include "utilities.hpp"

/**
\brief The base class that all dynamic arrays derive from,
i.e. arrays with size known at run-time. Defines extents for such arrays.
*/
template<typename T, size_t RANK>
class array_base_dynamic : public array_base<T, RANK>
{
public:
    using typename array_base<T, RANK>::extents_type;

	array_base_dynamic() { std::fill(std::begin(extents_), std::end(extents_), 0); }

	array_base_dynamic(const extents_type& extents) : extents_(extents) {}

	extents_type extents() const { return extents_; }

	template<size_t DIMENSION>
    size_t extent() const { return extents_[DIMENSION]; }

	size_t extent0() const { return extents_[0]; }
	size_t extent1() const { return extents_[1]; }
	size_t extent2() const { return extents_[2]; }
	size_t extent3() const { return extents_[3]; }
    size_t extent4() const { return extents_[4]; }
    size_t extent5() const { return extents_[5]; }
    size_t extent6() const { return extents_[6]; }
    size_t extent7() const { return extents_[7]; }
    size_t extent8() const { return extents_[8]; }
    size_t extent9() const { return extents_[9]; }

private:
	extents_type extents_;
};
