#pragma once

#include <array>

#include "darray.hpp"
#include "sarray.hpp"
#include "pdarray.hpp"
#include "psarray.hpp"

#include "geometry.hpp"

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
	auto darray1 = darray<float, 2>({ 2, 3 });
	auto darray2 = darray<float, 2>({ 2, 3 }, 1.f);
	auto darray3 = darray<float, 2>({ 2, 3 }, begin(darray1));
	auto darray4 = darray<float, 2>(darray1);
	auto darray5 = darray1;

	auto darray6  = darray<float>();
	auto darray7  = darray<float>({2});
	auto darray8  = darray<float>(2);
	auto darray9  = darray<float>(2, darray8.begin());
	auto darray10 = darray<float>({2}, darray8.begin());
	//auto darray11 = darray<float>(2, 3.f);
	auto darray12 = darray<float>({ 2 }, 3.f);
}

void test_construction_pdarray()
{
	auto ROWS = size_t{ 3 };
	auto COLUMNS = size_t{ 4 };
	auto N = ROWS * COLUMNS;
	auto vector0 = std::vector<float>(N);
	auto pdarray0 = pdarray<float>();
	auto pdarray1 = pdarray<float>(N, vector0.data());
	auto pdarray2 = pdarray<float>({ N }, vector0.data());
	auto pdarray3 = pdarray<float, 2>({ ROWS, COLUMNS }, vector0.data());
}

void test_construction_psarray()
{

}

void test_construction_mixed()
{
	auto sarray0   = sarray<float, 2, 3>();
	auto darray0   = darray<float, 2>({ 2, 3 });
	auto pdarray0  = pdarray<float, 2>({ 2, 3 }, data(darray0));
	auto psarray0  = psarray<float, 2, 3>(data(sarray0));
	auto cpdarray0 = pdarray<const float, 2>({ 2, 3 }, data(darray0));
	auto cpsarray0 = psarray<const float, 2, 3>(data(sarray0));

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

	auto pdarray1 = pdarray<float, 2>(sarray0);
	auto pdarray2 = pdarray<float, 2>(darray0);
	auto pdarray3 = pdarray<float, 2>(pdarray0);
	auto pdarray4 = pdarray<float, 2>(psarray0);

	// Should not compile:
	//auto pdarray5 = pdarray<float, 2>(cpdarray0);
	//auto pdarray6 = pdarray<float, 2>(cpsarray0);

	auto cpdarray1 = pdarray<const float, 2>(sarray0);
	auto cpdarray2 = pdarray<const float, 2>(darray0);
	auto cpdarray3 = pdarray<const float, 2>(pdarray0);
	auto cpdarray4 = pdarray<const float, 2>(psarray0);
	auto cpdarray5 = pdarray<const float, 2>(cpdarray0);
	auto cpdarray6 = pdarray<const float, 2>(cpsarray0);

	auto psarray1 = psarray<float, 2, 3>(sarray0);
	auto psarray2 = psarray<float, 2, 3>(darray0);
	auto psarray3 = psarray<float, 2, 3>(pdarray0);
	auto psarray4 = psarray<float, 2, 3>(psarray0);

	// Should not compile:
	//auto psarray5 = psarray<float, 2, 3>(cpdarray0);
	//auto psarray6 = psarray<float, 2, 3>(cpsarray0);

	auto cpsarray1 = psarray<const float, 2, 3>(sarray0);
	auto cpsarray2 = psarray<const float, 2, 3>(darray0);
	auto cpsarray3 = psarray<const float, 2, 3>(pdarray0);
	auto cpsarray4 = psarray<const float, 2, 3>(psarray0);
	auto cpsarray5 = psarray<const float, 2, 3>(cpdarray0);
	auto cpsarray6 = psarray<const float, 2, 3>(cpsarray0);
}
