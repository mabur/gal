#pragma once

#include <vector>
#include <array>
#include <valarray>

#include "sarray.hpp"
#include "darray.hpp"
#include "sarray_ptr.hpp"
#include "darray_ptr.hpp"

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

	auto pdarray1 = darray_ptr<const int>(std_array);
	auto pdarray2 = darray_ptr<const int>(std_vector);
	auto pdarray3 = darray_ptr<const int>(std_valarray);

	auto pdarray4 = darray_ptr<const int>(const_std_array);
	auto pdarray5 = darray_ptr<const int>(const_std_vector);
	auto pdarray6 = darray_ptr<const int>(const_std_valarray);

	auto pdarray7 = darray_ptr<int>(std_array);
	auto pdarray8 = darray_ptr<int>(std_vector);
	auto pdarray9 = darray_ptr<int>(std_valarray);

	// Should not compile:
	//auto pdarray10 = darray_ptr<int>(const_std_array);
	//auto pdarray11 = darray_ptr<int>(const_std_vector);
	//auto pdarray12 = darray_ptr<int>(const_std_valarray);
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

	auto psarray1 = sarray_ptr<const int, 1>(std_array);
	auto psarray2 = sarray_ptr<const int, 1>(std_vector);
	auto psarray3 = sarray_ptr<const int, 1>(std_valarray);

	auto psarray4 = sarray_ptr<const int, 1>(const_std_array);
	auto psarray5 = sarray_ptr<const int, 1>(const_std_vector);
	auto psarray6 = sarray_ptr<const int, 1>(const_std_valarray);

	auto psarray7 = sarray_ptr<int, 1>(std_array);
	auto psarray8 = sarray_ptr<int, 1>(std_vector);
	auto psarray9 = sarray_ptr<int, 1>(std_valarray);

	// Should not compile:
	//auto psarray10 = sarray_ptr<int, 1>(const_std_array);
	//auto psarray11 = sarray_ptr<int, 1>(const_std_vector);
	//auto psarray12 = sarray_ptr<int, 1>(const_std_valarray);
}