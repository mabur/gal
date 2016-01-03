#pragma once

#include <algorithm>

#include "arithmetic_traits.hpp"

////////////////////////////////////////////////////////////////////////////////
// add

template<typename IteratorIn1, typename IteratorIn2, typename IteratorOut,
	check_sum<value_type_i<IteratorIn1>, value_type_i<IteratorIn2>, value_type_i<IteratorOut>> = 0>
void add(IteratorIn1 left_begin, IteratorIn1 left_end, IteratorIn2 right_begin, IteratorOut out_begin)
{
	auto f = [](const auto& left, const auto& right) { return left + right; };
	std::transform(left_begin, left_end, right_begin, out_begin, f);
}

template<typename ElementIn, typename IteratorIn, typename IteratorOut,
	check_sum<ElementIn, value_type_i<IteratorIn>, value_type_i<IteratorOut>> = 0>
void add(const ElementIn& left, IteratorIn right_begin, IteratorIn right_end, IteratorOut out_begin)
{
	auto f = [&](const auto& right) { return left + right; };
	std::transform(right_begin, right_end, out_begin, f);
}

template<typename IteratorIn, typename ElementIn, typename IteratorOut,
	check_sum<value_type_i<IteratorIn>, ElementIn, value_type_i<IteratorOut>> = 0>
void add(IteratorIn left_begin, IteratorIn left_end, const ElementIn& right, IteratorOut out_begin)
{
	auto f = [&](const auto& left) { return left + right; };
	std::transform(left_begin, left_end, out_begin, f);
}

////////////////////////////////////////////////////////////////////////////////
// subtract

template<typename IteratorIn1, typename IteratorIn2, typename IteratorOut,
	check_difference<value_type_i<IteratorIn1>, value_type_i<IteratorIn2>, value_type_i<IteratorOut>> = 0>
void subtract(IteratorIn1 left_begin, IteratorIn1 left_end, IteratorIn2 right_begin, IteratorOut out_begin)
{
	auto f = [](const auto& left, const auto& right) { return left - right; };
	std::transform(left_begin, left_end, right_begin, out_begin, f);
}

template<typename ElementIn, typename IteratorIn, typename IteratorOut,
	check_difference<ElementIn, value_type_i<IteratorIn>, value_type_i<IteratorOut>> = 0>
void subtract(const ElementIn& left, IteratorIn right_begin, IteratorIn right_end, IteratorOut out_begin)
{
	auto f = [&](const auto& right) { return left - right; };
	std::transform(right_begin, right_end, out_begin, f);
}

template<typename IteratorIn, typename ElementIn, typename IteratorOut,
	check_difference<value_type_i<IteratorIn>, ElementIn, value_type_i<IteratorOut>> = 0>
void subtract(IteratorIn left_begin, IteratorIn left_end, const ElementIn& right, IteratorOut out_begin)
{
	auto f = [&](const auto& left) { return left - right; };
	std::transform(left_begin, left_end, out_begin, f);
}

////////////////////////////////////////////////////////////////////////////////
// multiply

template<typename IteratorIn1, typename IteratorIn2, typename IteratorOut,
	check_product<value_type_i<IteratorIn1>, value_type_i<IteratorIn2>, value_type_i<IteratorOut>> = 0>
void multiply(IteratorIn1 left_begin, IteratorIn1 left_end, IteratorIn2 right_begin, IteratorOut out_begin)
{
	auto f = [](const auto& left, const auto& right) { return left * right; };
	std::transform(left_begin, left_end, right_begin, out_begin, f);
}

template<typename ElementIn, typename IteratorIn, typename IteratorOut,
	check_product<ElementIn, value_type_i<IteratorIn>, value_type_i<IteratorOut>> = 0>
void multiply(const ElementIn& left, IteratorIn right_begin, IteratorIn right_end, IteratorOut out_begin)
{
	auto f = [&](const auto& right) { return left * right; };
	std::transform(right_begin, right_end, out_begin, f);
}

template<typename IteratorIn, typename ElementIn, typename IteratorOut,
	check_product<value_type_i<IteratorIn>, ElementIn, value_type_i<IteratorOut>> = 0>
void multiply(IteratorIn left_begin, IteratorIn left_end, const ElementIn& right, IteratorOut out_begin)
{
	auto f = [&](const auto& left) { return left * right; };
	std::transform(left_begin, left_end, out_begin, f);
}

////////////////////////////////////////////////////////////////////////////////
// divide

template<typename IteratorIn1, typename IteratorIn2, typename IteratorOut,
	check_ratio<value_type_i<IteratorIn1>, value_type_i<IteratorIn2>, value_type_i<IteratorOut>> = 0>
void divide(IteratorIn1 left_begin, IteratorIn1 left_end, IteratorIn2 right_begin, IteratorOut out_begin)
{
	auto f = [](const auto& left, const auto& right) { return left / right; };
	std::transform(left_begin, left_end, right_begin, out_begin, f);
}

template<typename ElementIn, typename IteratorIn, typename IteratorOut,
	check_ratio<ElementIn, value_type_i<IteratorIn>, value_type_i<IteratorOut>> = 0>
void divide(const ElementIn& left, IteratorIn right_begin, IteratorIn right_end, IteratorOut out_begin)
{
	auto f = [&](const auto& right) { return left / right; };
	std::transform(right_begin, right_end, out_begin, f);
}

template<typename IteratorIn, typename ElementIn, typename IteratorOut,
	check_ratio<value_type_i<IteratorIn>, ElementIn, value_type_i<IteratorOut>> = 0>
void divide(IteratorIn left_begin, IteratorIn left_end, const ElementIn& right, IteratorOut out_begin)
{
	auto f = [&](const auto& left) { return left / right; };
	std::transform(left_begin, left_end, out_begin, f);
}
