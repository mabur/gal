#pragma once
/*
#include <array>

#include "sarray.hpp"
#include "darray.hpp"
#include "sarray_ptr.hpp"
#include "darray_ptr.hpp"

#include "vector_math.hpp"

void testArithmeticDynamicArrays()
{
	std::array<size_t, 2> sizes = { 2, 3 };
	auto f = darray<float, 2>(sizes);
	auto g = f;
	auto h = f + g;
	auto i = f - g;
	auto j = f * 3.f;
	auto k = 3.f * f;
	auto l = f / 4.f;
	g += f;
	g -= f;
	g *= 2.f;
	g /= 7.f;
}

void testArithmeticStaticArrays()
{
	auto f = sarray<float, 2, 3>();
	auto g = f;
	auto h = f + g;
	auto i = f - g;
	auto j = f * 3.f;
	auto k = 3.f * f;
	auto l = f / 4.f;
	g += f;
	g -= f;
	g *= 2.f;
	g /= 7.f;
}

void testArithmeticPointerArrays()
{
	auto e = sarray<float, 2, 3>();
	auto f = darray_ptr<const float, 2>({ 2, 3 }, e.data());

	auto d = sarray<float, 2, 3>();
	auto g = darray_ptr<float, 2>({ 2, 3 }, d.data());

	g += f;
	g -= f;
	g *= 2.f;
	g /= 7.f;
}

void testArithmeticPointerStaticArrays()
{
	auto e = sarray<float, 2, 3>();
	auto f = sarray_ptr<const float, 2, 3>(e.data());

	auto d = sarray<float, 2, 3>();
	auto g = sarray_ptr<float, 2, 3>(d.data());

	g += f;
	g -= f;
	g *= 2.f;
	g /= 7.f;
}

void testArithmeticMixedArrays()
{
	std::array<size_t, 2> sizes = { 2, 3 };

	auto e = sarray<float, 2, 3>();
	auto f = darray_ptr<const float, 2>({ 2, 3 }, e.data());

	auto d = darray<float, 2>(sizes);
	auto g = darray_ptr<float, 2>({ 2, 3 }, d.data());

	// TODO: aliasing?

	d += d;
	d += e;
	d += f;
	d += g;

	e += d;
	e += e;
	e += f;
	e += g;

	g += d;
	g += e;
	g += f;
	g += g;

	d -= d;
	d -= e;
	d -= f;
	d -= g;

	e -= d;
	e -= e;
	e -= f;
	e -= g;

	g -= d;
	g -= e;
	g -= f;
	g -= g;
}
*/