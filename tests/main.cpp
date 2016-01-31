#include <iostream>
#include <vector>
#include <array>
#include <valarray>

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

auto a = pdarray<int, 2>({2, 3}, data_iterator);
auto a = pdarray<int, 2>(data_array);

auto a = psarray<int, 2, 3>(data_iterator);
auto a = psarray<int, 2, 3>(data_array);

auto a = std::array<int, 2>({1, 2})
auto a = std::vector<int>(size)
auto a = std::vector<int>(size, data_value)
auto a = std::valarray<int>(size)
auto a = std::valarray<int>(data_value, size) <- exception

assert(extents(array1) == extents(array2))
*/

void f(pdarray<int> a)
{
	for (auto& x : a)
	{
		++x;
	}
}

void h(pdarray<const int> a)
{
	using namespace std;
	for (auto& x : a)
	{
		cout << x << " ";
	}
	cout << endl;
}

void g(pdarray<int, 2> a)
{
	for (auto& x : a)
	{
		++x;
	}

	for (size_t y = 0; y < a.extent1(); ++y)
	{
		for (size_t x = 0; x < a.extent0(); ++x)
		{
			std::cout << a(x, y) << " ";
		}
		std::cout << std::endl;
	}
}

template<typename Array2d>
void fill_and_print_array2d(Array2d& array)
{
    assert(array.rank() == 2);

    for (int i = 0; i < array.size(); ++i)
    {
        array[i] = i;
    }

    for (auto& element : array)
    {
        element += 10;
    }
    
    using namespace std;

    for (int y = 0; y < array.extent1(); ++y)
    {
        for (int x = 0; x < array.extent0(); ++x)
        {
            cout << array(x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
	using namespace std;

	cout << "total_size: " << total_size<1, 2, 3>::value << endl;

	cout << "get_extent0: " << get_size<0, 8, 9, 6, 5>::value << endl;
	cout << "get_extent1: " << get_size<1, 8, 9, 6, 5>::value << endl;
	cout << "get_extent2: " << get_size<2, 8, 9, 6, 5>::value << endl;
	cout << "get_extent3: " << get_size<3, 8, 9, 6, 5>::value << endl;

	const auto W = size_t(4);
	const auto H = size_t(3);
	const auto N = W * H;

	auto a = vector<int>(N);
	//auto b = valarray<int>(N);
	auto c = array<int, N>();

	f(pdarray<int>(a));
	//f(b);
	f(pdarray<int>(c));

	h(pdarray<const int>(a));
	h(pdarray<const int>(c));

	g(pdarray<int, 2>({W, H}, a.data()));
	g(pdarray<int, 2>({W, H}, c.data()));

	auto d = darray<int>();
	auto e = sarray<int, 5>();
	auto M = sarray<int, 2, 3>();

	std::array<size_t, 2> sizes = {2, 3};
    auto f = darray<float, 2>({2, 3});
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
    auto static_array2d = sarray<float, 3, 2>();
    auto dynamic_array2d = darray<int, 2>({ 8, 4 });
    fill_and_print_array2d(static_array2d);
    fill_and_print_array2d(dynamic_array2d);

	for (auto x : f)
	{
		std::ignore = x;
	}

	for (size_t y = 0; y < f.extent1(); ++y)
		for (size_t x = 0; x < f.extent0(); ++x)
			f(x, y);

    for (size_t i = 0; i < f.size(); ++i)
        f[i];

	M.size();
	M.rank();
	M.extent0();
	M.extent1();

	// Row-major order for images.
	for (size_t y = 0; y < M.extent1(); ++y)
		for (size_t x = 0; x < M.extent0(); ++x)
			M(x, y);

	// Column-major order for matrices.
	for (size_t col = 0; col < M.extent1(); ++col)
		for (size_t row = 0; row < M.extent0(); ++row)
			M(row, col);

	testVectors();
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
