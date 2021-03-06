#pragma once

#include <array>

#include "darray.hpp"
#include "sarray.hpp"
#include "darray_ptr.hpp"
#include "sarray_ptr.hpp"

#include "geometry.hpp"

namespace gal
{

void test_construction_documentation_sarray1()
{
    const auto N = size_t{ 10 };
    const auto M = size_t{ 20 };
    const auto L = size_t{ 30 };
    auto array0 = std::array<float, N>();
    auto array1 = sarray<float, N>();
    auto array2 = sarray<float, N, M>();
    auto array3 = sarray<float, N, M, L>();
}

void test_construction_documentation_darray1()
{
    auto N = size_t{ 10 };
    auto M = size_t{ 20 };
    auto L = size_t{ 30 };
    auto array1 = darray<float, 1>(N);
    auto array2 = darray<float, 2>(N, M);
    auto array3 = darray<float, 3>(N, M, L);
}

void test_construction_documentation_sarray2()
{
    const auto N = size_t{ 10 };
    const auto M = size_t{ 20 };
    auto value = 6.283f;
    auto array1 = sarray<float, N>(value);
    auto array2 = sarray<float, N, M>(value);
}

void test_construction_documentation_sarray3()
{
    const auto N = size_t{ 10 };
    const auto M = size_t{ 20 };
    auto array0 = std::array<float, N * M>();
    auto data_pointer = array0.data();
    auto array1 = sarray<float, N>(data_pointer);
    auto array2 = sarray<float, N, M>(data_pointer);
}

void test_construction_documentation_psarray()
{
    const auto N = size_t{ 10 };
    const auto M = size_t{ 20 };
    auto array0 = std::array<float, N * M>();
    auto data_pointer = array0.data();
    auto array1 = sarray_ptr<float, N>(data_pointer);
    auto array2 = sarray_ptr<float, N, M>(data_pointer);
}

void test_construction_documentation_psarray2()
{
    const auto N = size_t{ 10 };
    const auto M = size_t{ 20 };
    const auto array0 = std::array<float, N * M>();
    const auto data_pointer = array0.data();
    auto array1 = sarray_ptr<const float, N>(data_pointer);
    auto array2 = sarray_ptr<const float, N, M>(data_pointer);
}

void test_construction_documentation_darray2()
{
    auto N = size_t{ 10 };
    auto array0 = darray<float>(N);
    auto array1 = darray<float>(N);
    auto array2 = darray<float, 1>(N);
    auto array3 = darray<float, 1>(N);
}

void test_construction_documentation_darray3()
{
    auto N = size_t{ 10 };
    auto M = size_t{ 20 };
    auto value = 6.283f;
    auto array1 = std::vector<float>(N, value);
    auto array2 = darray<float>(N, value);
    auto array3 = darray<float, 2>(N, M, value);
}

void test_construction_documentation_darray4()
{
    auto N = size_t{ 10 };
    auto M = size_t{ 20 };
    auto array1 = std::vector<float>(N * M);
    auto data_pointer = array1.data();
    auto array2 = darray<float>(N, data_pointer);
    auto array3 = darray<float, 2>(N, M, data_pointer);
}

void test_construction_documentation_pdarray()
{
    auto N = size_t{ 10 };
    auto M = size_t{ 20 };
    auto array1 = std::vector<float>(N * M);
    auto data_pointer = array1.data();
    auto array2 = darray_ptr<float>(N, data_pointer);
    auto array3 = darray_ptr<float, 2>(N, M, data_pointer);
}

void test_construction_documentation_pdarray2()
{
    auto N = size_t{ 10 };
    auto M = size_t{ 20 };
    const auto array1 = std::vector<float>(N * M);
    const auto data_pointer = array1.data();
    auto array2 = darray_ptr<const float>(N, data_pointer);
    auto array3 = darray_ptr<const float, 2>(N, M, data_pointer);
}

void test_construction_sarray()
{
	auto sarray0 = sarray<float, 2>();
	auto sarray1 = sarray<float, 2>({ 1.f, 1.f });
	auto sarray2 = sarray<float, 2, 3>();
	auto sarray3 = sarray<float, 2, 3>(sarray2);
	auto sarray4 = sarray<float, 3, 2>({1.f, 2.f, 2.f, 3.f, 4.f, 5.f });
	auto sarray5 = sarray<float, 3, 2>(1.f);
	auto sarray6 = sarray<float, 3, 3>(begin(sarray5));
}

void test_construction_darray()
{
	auto darray0 = darray<float, 2>();
	auto darray1 = darray<float, 2>(2, 3 );
	auto darray2 = darray<float, 2>(2, 3, 1.f);
	auto darray3 = darray<float, 2>(2, 3, begin(darray1));
	auto darray4 = darray<float, 2>(darray1);
	auto darray5 = darray1;

	auto darray6  = darray<float>();
	auto darray7  = darray<float>(2);
	auto darray8  = darray<float>(2);
	auto darray9  = darray<float>(2, darray8.begin());
	auto darray10 = darray<float>(2, darray8.begin());
	auto darray11 = darray<float>(2, 3.f);
	auto darray12 = darray<float>(2, 3.f);

    auto darray13 = darray<float, 2>(1, 2);
    auto darray14 = darray<float, 2>(1, 2, 3.f);
}

void test_construction_pdarray()
{
	auto ROWS = size_t{ 3 };
	auto COLUMNS = size_t{ 4 };
	auto N = ROWS * COLUMNS;
	auto vector0 = std::vector<float>(N);
	auto pdarray0 = darray_ptr<float>();
	auto pdarray1 = darray_ptr<float>(N, vector0.data());
	auto pdarray2 = darray_ptr<float>(N, vector0.data());
	auto pdarray3 = darray_ptr<float, 2>(ROWS, COLUMNS, vector0.data());
}

void test_construction_psarray()
{
    const auto ROWS = size_t{ 3 };
    const auto COLUMNS = size_t{ 4 };
    const auto N = ROWS * COLUMNS;
    auto vector0 = std::vector<float>(N);

    auto psarray0 = sarray_ptr<float, N>();
    auto psarray1 = sarray_ptr<float, N>(vector0.data());
    auto psarray2 = sarray_ptr<float, N>(vector0);
}

void test_construction_mixed()
{
	auto sarray0   = sarray<float, 2, 3>();
	auto darray0   = darray<float, 2>(2, 3);
	auto pdarray0  = darray_ptr<float, 2>(2, 3, data(darray0));
	auto psarray0  = sarray_ptr<float, 2, 3>(data(sarray0));
	auto cpdarray0 = darray_ptr<const float, 2>(2, 3, data(darray0));
	auto cpsarray0 = sarray_ptr<const float, 2, 3>(data(sarray0));

	auto darray1 = darray<float, 2>(sarray0);
	auto darray2 = darray<float, 2>(darray0);
	auto darray3 = darray<float, 2>(pdarray0);
	auto darray4 = darray<float, 2>(psarray0);
	auto darray5 = darray<float, 2>(cpdarray0);
	auto darray6 = darray<float, 2>(cpsarray0);

	auto sarray1 = sarray<float, 2, 3>(sarray0);
	auto sarray2 = sarray<float, 2, 3>(darray0);
	auto sarray3 = sarray<float, 2, 3>(pdarray0);
	auto sarray4 = sarray<float, 2, 3>(psarray0);
	auto sarray5 = sarray<float, 2, 3>(cpdarray0);
	auto sarray6 = sarray<float, 2, 3>(cpsarray0);

	auto pdarray1 = darray_ptr<float, 2>(sarray0);
	auto pdarray2 = darray_ptr<float, 2>(darray0);
	auto pdarray3 = darray_ptr<float, 2>(pdarray0);
	auto pdarray4 = darray_ptr<float, 2>(psarray0);

	// Should not compile:
	//auto pdarray5 = darray_ptr<float, 2>(cpdarray0);
	//auto pdarray6 = darray_ptr<float, 2>(cpsarray0);

	auto cpdarray1 = darray_ptr<const float, 2>(sarray0);
	auto cpdarray2 = darray_ptr<const float, 2>(darray0);
	auto cpdarray3 = darray_ptr<const float, 2>(pdarray0);
	auto cpdarray4 = darray_ptr<const float, 2>(psarray0);
	auto cpdarray5 = darray_ptr<const float, 2>(cpdarray0);
	auto cpdarray6 = darray_ptr<const float, 2>(cpsarray0);

	auto psarray1 = sarray_ptr<float, 2, 3>(sarray0);
	auto psarray2 = sarray_ptr<float, 2, 3>(darray0);
	auto psarray3 = sarray_ptr<float, 2, 3>(pdarray0);
	auto psarray4 = sarray_ptr<float, 2, 3>(psarray0);

	// Should not compile:
	//auto psarray5 = sarray_ptr<float, 2, 3>(cpdarray0);
	//auto psarray6 = sarray_ptr<float, 2, 3>(cpsarray0);

	auto cpsarray1 = sarray_ptr<const float, 2, 3>(sarray0);
	auto cpsarray2 = sarray_ptr<const float, 2, 3>(darray0);
	auto cpsarray3 = sarray_ptr<const float, 2, 3>(pdarray0);
	auto cpsarray4 = sarray_ptr<const float, 2, 3>(psarray0);
	auto cpsarray5 = sarray_ptr<const float, 2, 3>(cpdarray0);
	auto cpsarray6 = sarray_ptr<const float, 2, 3>(cpsarray0);
}

} // namespace gal
