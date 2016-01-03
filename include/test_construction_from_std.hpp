#pragma once

#include <vector>
#include <array>
#include <valarray>

#include "sarray.hpp"
#include "darray.hpp"
#include "psarray.hpp"
#include "pdarray.hpp"

inline void sarray_from_std()
{
	const auto N = size_t(5);

	auto std_array    = std::array<int, N>();
	auto std_vector   = std::vector<int>(N);
	auto std_valarray = std::valarray<int>(N);
	//int carray[N];

	auto const_std_array    = std::array<int, N>();
	auto const_std_vector   = std::vector<int>(N);
	auto const_std_valarray = std::valarray<int>(N);
	//int const_carray[N];

	auto sarray0 = sarray<int, 1>(std_array);
	auto sarray1 = sarray<int, 1>(std_vector);
	auto sarray2 = sarray<int, 1>(std_valarray);

	auto sarray3 = sarray<int, 1>(const_std_array);
	auto sarray4 = sarray<int, 1>(const_std_vector);
	auto sarray5 = sarray<int, 1>(const_std_valarray);
}

inline void darray_from_std()
{
	const auto N = size_t(5);

	auto std_array    = std::array<int, N>();
	auto std_vector   = std::vector<int>(N);
	auto std_valarray = std::valarray<int>(N);
	//int carray[N];

	const auto const_std_array    = std::array<int, N>();
	const auto const_std_vector   = std::vector<int>(N);
	const auto const_std_valarray = std::valarray<int>(N);
	//int const_carray[N];

	auto darray0 = darray<int>(std_array);
	auto darray1 = darray<int>(std_vector);
	auto darray2 = darray<int>(std_valarray);

	auto darray3 = darray<int>(const_std_array);
	auto darray4 = darray<int>(const_std_vector);
	auto darray5 = darray<int>(const_std_valarray);
}

inline void pdarray_from_std()
{
	const auto N = size_t(5);

	auto std_array    = std::array<int, N>();
	auto std_vector   = std::vector<int>(N);
	auto std_valarray = std::valarray<int>(N);
	//int carray[N];

	const auto const_std_array    = std::array<int, N>();
	const auto const_std_vector   = std::vector<int>(N);
	const auto const_std_valarray = std::valarray<int>(N);
	//int const_carray[N];

	auto pdarray1 = pdarray<const int>(std_array);
	auto pdarray2 = pdarray<const int>(std_vector);
	auto pdarray3 = pdarray<const int>(std_valarray);

	auto pdarray4 = pdarray<const int>(const_std_array);
	auto pdarray5 = pdarray<const int>(const_std_vector);
	auto pdarray6 = pdarray<const int>(const_std_valarray);

	auto pdarray7 = pdarray<int>(std_array);
	auto pdarray8 = pdarray<int>(std_vector);
	auto pdarray9 = pdarray<int>(std_valarray);

	// Should not compile:
	//auto pdarray10 = pdarray<int>(const_std_array);
	//auto pdarray11 = pdarray<int>(const_std_vector);
	//auto pdarray12 = pdarray<int>(const_std_valarray);
}

inline void psarray_from_std()
{
	const auto N = size_t(5);

	auto std_array    = std::array<int, N>();
	auto std_vector   = std::vector<int>(N);
	auto std_valarray = std::valarray<int>(N);
	//int carray[N];

	const auto const_std_array    = std::array<int, N>();
	const auto const_std_vector   = std::vector<int>(N);
	const auto const_std_valarray = std::valarray<int>(N);
	//int const_carray[N];

	auto psarray1 = psarray<const int, 1>(std_array);
	auto psarray2 = psarray<const int, 1>(std_vector);
	auto psarray3 = psarray<const int, 1>(std_valarray);

	auto psarray4 = psarray<const int, 1>(const_std_array);
	auto psarray5 = psarray<const int, 1>(const_std_vector);
	auto psarray6 = psarray<const int, 1>(const_std_valarray);

	auto psarray7 = psarray<int, 1>(std_array);
	auto psarray8 = psarray<int, 1>(std_vector);
	auto psarray9 = psarray<int, 1>(std_valarray);

	// Should not compile:
	//auto psarray10 = psarray<int, 1>(const_std_array);
	//auto psarray11 = psarray<int, 1>(const_std_vector);
	//auto psarray12 = psarray<int, 1>(const_std_valarray);
}