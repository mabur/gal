#include <iostream>
#include <vector>
#include <array>
#include <valarray>
#include <numeric>

#include "gal.hpp"

#include "test_construction.hpp"
#include "test_construction_from_std.hpp"
#include "test_arithmetic.hpp"

#include "test_geometry.hpp"

/*
* L�gg till transpose-funktion.

* sliced_array, med stride, l�gg till. Finns det n�n kort bokstav f�r det?
  Vill man bara ha strided f�r pointer arrays? Kan heta spsarray och spdarray.

Fr�gor
* copy-construction fr�n samma typ. Hanteras det av de templatiserade konstrukt�rerna?
* Single-dimensional construction from:
  - Eigen::Matrix

* Implicit konvertering? F�r �gande arrayer: Nej. F�r pekare ?

* Hur ska nullptr hanteras? Ska man kr�va att size()==0 d�?

* make_pdarray({1,2,4}, data); // S� man slipper redundanta template argument.
  make_darray({1,2}, 0.f);
  make_sarray({1, 2}, 1.f);

* Hur ska multiplikation och division hanteras? Vill kunna hantera fallen:
  - Elementvis
  - Matriser
  - Komplexa tal
  - Kvaternioner
  - Expression templates
* Ha m�nga elementvisa operationer i annan modul: * / % < <= > >= && ! ||.
* implementera som allm�nna funktioner: add, subtract, multiply, divide.

* storage order f�r matriser.
- Skulle kunna ha allm�n default-templatiserad flagga i class-signature.
-  Eller kan l�ta den bara p�verka operator() !.
D� kan man s�tta den typ:
using matrix23f = sarray<float,2,3,ROW_MAJOR>
- Skapa matris-klass som �rver fr�n sarray? Vore ju b�ttre om man inte beh�vde �rva fr�n den.
- Skapa tv� fria funktioner f�r operator(), som kan v�lja mellan att plocka ut i row-major eller column major.
at_cm(matrix, 3, 2)
at_rm(matrix, 2, 3)
at_cm<3,2>(matrix)
at_rm<2,3>(matrix)

* Hur ska konstruktorerna vara f�r att dom ska vara konsekventa f�r alla arrayer?
  - typ, dimension, storlek, v�rden.

auto a = sarray<int, 2, 3>(1, 2, 3, 4, 5, 6);   // <- funkar nog inte det bra f�r matriser i den column/row-order som vi har?
auto a = sarray<int, 2, 3>({1, 2, 3, 4, 5, 6}); // <- 
auto a = sarray<int, 2, 3>({{1, 2, 3}, {4, 5, 6}}); // <-
auto a = sarray<int, 2, 3>(data_iterator);
auto a = sarray<int, 2, 3>(data_value);
auto a = sarray<int, 2, 3>(data_array);

auto a = darray<int, 2>({2, 3}, data_iterator); // Till�t iterator ist�llet f�r pekare?
auto a = darray<int, 2>({2, 3}, data_value);
auto a = darray<int, 2>({2, 3});
auto a = darray<int, 2>(data_array);

auto a = darray_ptr<int, 2>({2, 3}, data_iterator);
auto a = darray_ptr<int, 2>(data_array);

auto a = sarray_ptr<int, 2, 3>(data_iterator);
auto a = sarray_ptr<int, 2, 3>(data_array);

auto a = std::array<int, 2>({1, 2})
auto a = std::vector<int>({data1, data2})
auto a = std::vector<int>(size)
auto a = std::vector<int>(size, data_value)
auto a = std::valarray<int>(size)
auto a = std::valarray<int>(data_value, size) <- exception

assert(extents(array1) == extents(array2))
*/

using namespace gal;

void f(darray_ptr<int> a)
{
	for (auto& x : a)
	{
		++x;
	}
}

void h(darray_ptr<const int> a)
{
	using namespace std;
	for (auto& x : a)
	{
		cout << x << " ";
	}
	cout << endl;
}

void g(darray_ptr<int, 2> a)
{
	for (auto& x : a)
	{
		++x;
	}

	for (size_t y = 0; y < extent1(a); ++y)
	{
		for (size_t x = 0; x < extent0(a); ++x)
		{
			std::cout << a(x, y) << " ";
		}
		std::cout << std::endl;
	}
}

// Function that works on any of the four array classes in GAL:
template<typename array_2d>
void fill_array_2d(array_2d& array)
{
    // Check the rank of the array, i.e. the number of dimensions:
    assert(array.rank() == 2);
    // Get the value_type of of an array similar to standard containers:
    using value_type = typename array_2d::value_type;

    for (size_t i = 0; i < array.size(); ++i)
    {
        // Access array data with linear index, using operator[]:
        array[i] = static_cast<value_type>(i);
    }

    // Use array in range based for loop:
    for (auto& element : array)
    {
        element += 10;
    }
}

// Function that works on any of the four array classes in GAL:
template<typename array_2d>
void print_array_2d(const array_2d& array)
{
    // Check the rank of the array, i.e. the number of dimensions:
    assert(array.rank() == 2);
    using namespace std;

    // Loop over the extent of each dimension:
    for (size_t y = 0; y < extent1(array); ++y)
    {
        for (size_t x = 0; x < extent0(array); ++x)
        {
            // Access array data with multi-dimensional index, using operator():
            cout << array(x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
	using namespace std;
    using namespace gal;

	cout << "total_size: " << details::total_size<1, 2, 3>::value << endl;

	const auto W = size_t(4);
	const auto H = size_t(3);
	const auto N = W * H;

	auto a = vector<int>(N);
	//auto b = valarray<int>(N);
	auto c = array<int, N>();

	f(darray_ptr<int>(a));
	//f(b);
	f(darray_ptr<int>(c));

	h(darray_ptr<const int>(a));
	h(darray_ptr<const int>(c));

	g(darray_ptr<int, 2>(W, H, a.data()));
	g(darray_ptr<int, 2>(W, H, c.data()));

	auto d = darray<int>();
	auto e = sarray<int, 5>();
	auto M = sarray<int, 2, 3>();

	std::array<size_t, 2> sizes = {2, 3};
    auto f = darray<float, 2>(2, 3);
	auto g = f;

	begin(e);
	end(e);
	data(e);
	size(e);

	begin(f);
	end(f);
	data(f);
	size(f);
	
    cout << "print array" << endl;

    using namespace gal;
    using namespace std;

    // Create array containers that own their data:
    auto static_array_2d = sarray<float, 3, 3>();
    auto dynamic_array_2d = darray<int, 2>(4, 4);

    // Create arrays that points to data owned by someone else:
    auto static_array_ptr_2d = sarray_ptr<float, 3, 2>(static_array_2d.data());
    auto dynamic_array_ptr_2d = darray_ptr<int, 2>(4, 2, dynamic_array_2d.data());

    fill_array_2d(static_array_2d);
    fill_array_2d(dynamic_array_2d);

    cout << "Data of owning arrays: " << endl;
    print_array_2d(static_array_2d);
    print_array_2d(dynamic_array_2d);

    cout << "Data pointed to by non-owning arrays: " << endl;
    print_array_2d(static_array_ptr_2d);
    print_array_2d(dynamic_array_ptr_2d);

	for (auto x : f)
	{
		std::ignore = x;
	}

	for (size_t y = 0; y < extent1(f); ++y)
		for (size_t x = 0; x < extent0(f); ++x)
			f(x, y);

    for (size_t i = 0; i < f.size(); ++i)
        f[i];

	M.size();
	M.rank();
	M.extent<0>();
	M.extent<1>();

	// Row-major order for images.
	for (size_t y = 0; y < extent1(M); ++y)
		for (size_t x = 0; x < extent0(M); ++x)
			M(x, y);

	// Column-major order for matrices.
	for (size_t col = 0; col < extent1(M); ++col)
		for (size_t row = 0; row < extent0(M); ++row)
			M(row, col);

	testVectors();
    testMatrices();
	/*
	testArithmeticStaticArrays();
	testArithmeticDynamicArrays();
	testArithmeticPointerArrays();
	testArithmeticMixedArrays();
	*/
	cout << "Press enter to quit." << endl;
	cin.get();

	//sarray<int, 3, 3, 3, 3, 6> magnus;
	//magnus.get_element(magnus, 1, 1, 1, 1, 1);
}
