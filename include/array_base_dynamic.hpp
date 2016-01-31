#pragma once

#include "array_base.hpp"

#include <algorithm>
#include <array>

template<size_t size> inline size_t product(const size_t* array);

template<> inline
size_t product<0>(const size_t*)
{
	return 1;
}

template<size_t size> inline
size_t product(const size_t* array)
{
	return array[0] * product<size - 1>(array + 1);
}

template<size_t size> inline
size_t product(const std::array<size_t, size>& array)
{
    return product<size>(&array.front());
}

template<typename T, size_t RANK>
class array_base_dynamic : public array_base<T, RANK>
{
public:
    using Extents = typename array_base<T, RANK>::Extents;// std::array<size_t, D>;

	array_base_dynamic() { std::fill(std::begin(extents_), std::end(extents_), 0); }

	array_base_dynamic(const Extents& extents) : extents_(extents) {}

	Extents extents() const { return extents_; }

	template<size_t d> size_t extent() const { return extents_[d]; }

	size_t extent0() const { return extents_[0]; }
	size_t extent1() const { return extents_[1]; }
	size_t extent2() const { return extents_[2]; }
	size_t extent3() const { return extents_[3]; }

private:
	Extents extents_;
};
