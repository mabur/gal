#pragma once

#include <assert.h>
#include "geometry.hpp"

void testVectors()
{
	auto vector0 = vector1f{};
	auto vector1 = vector2f{ 1.f, 2.f };
	auto vector2 = vector3f{ 1.f, 2.f, 3.f };
	auto vector3 = vector4f{ 1.f, 2.f, 3.f, 4.f };
	
	//auto e = dot(vector1, vector1);
	////auto f = project(vector2, vector2);
	//auto g = norm(vector1);
	//auto h = squared_norm(vector1);
}

void testMatrices()
{
	/*
	auto matrix0 = matrix23f{
	1.f, 2.f, 3.f,
	4.f, 5.f, 6.f };
	*/
	// TODO: make_matrix23f(1.f, 2.f, 3.f, 4.f, 5.f, 6.f );
	// TODO: make_matrix23 (1.f, 2.f, 3.f, 4.f, 5.f, 6.f );
	auto matrix0 = make_matrix23f({
		1.f, 2.f, 3.f,
		4.f, 5.f, 6.f });

	assert(matrix0(0, 0) == 1.f);
	assert(matrix0(0, 1) == 2.f);
	assert(matrix0(0, 2) == 3.f);
	assert(matrix0(1, 0) == 4.f);
	assert(matrix0(1, 1) == 5.f);
	assert(matrix0(1, 2) == 6.f);

	assert(   rows(matrix0) == 2);
	assert(columns(matrix0) == 3);
}
