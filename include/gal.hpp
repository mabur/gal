/** \mainpage

# Overview of GAL

This library consists of four different array classes:
```
        | Owns Memory         Non Owning Pointer
--------|---------------------------------------
Static  | gal::sarray         gal::sarray_ptr
Dynamic | gal::darray         gal::darray_ptr
```
The size of a static array is known at compile time.
The size of a dynamic array is known at run time.
The arrays that own memory are containers, similar to those in the standard
template library [STL](http://www.cplusplus.com/reference/stl/).
The non owning arrays just point to an array owned by
someone else. They can point to any array, e.g. an array from another library.

All four array types in GAL support multiple dimensions. Furthermore, they all
assume contiguous memory. There is no support for strided arrays.

GAL provides array interfaces that are consistent across these four use cases,
while also being consistent with the arrays in the standard library.

# Other Array Libraries

The standard template library [STL](http://www.cplusplus.com/reference/stl/) has
some array containers:
```
        | Owns Memory         Non Owning Pointer
--------|---------------------------------------
Static  | std::array          -
Dynamic | std::vector         -
        | std::valarray
```
STL has no class for multi-dimensional arrays or any class for
representing non owning pointers to general arrays.
The Guidelines Support Library [GSL](https://github.com/Microsoft/GSL) has a
class that represents a non owning pointer to a single-dimensional dynamic array:
```
        | Owns Memory         Non Owning Pointer
--------|---------------------------------------
Static  | -                   -
Dynamic | -                   gsl::span
```
[The Boost Multidimensional Array Library]
(http://www.boost.org/doc/libs/1_60_0/libs/multi_array/doc/index.html)
has support for multi-dimensional dynamic arrays:
```
        | Owns Memory         Non Owning Pointer
--------|-------------------------------------------------
Static  | -                   -
Dynamic | boost::multi_array  boost::multi_array_ref
        |                     boost::const_multi_array_ref
```
GAL attempts to fill in the gaps between these libraries and provide a
consistent interface.


# Common interface for arrays in GAL

The following holds for all of the arrays in GAL:
- The elements are stored contiguously in memory. Strided arrays are not supported.
- The element with index `i` of array `a` is retrieved as `a[i]`.
- The indexing of the elements starts at `0`.
- The number of elements is retrieved by calling the member function `size()`.
      - The size of a static array is known at compile time.
      - The size of a dynamic array is known at run time.
- The elements might be structured over multiple dimensions.
  The number of dimensions is retrieved by calling the member function `rank()`.
  The rank is known at compile time for all arrays.
- The array has an extent in each dimension.
  The size of the array is the product of all its extents.
      - The extents of a static array is known at compile time.
      - The extent of a dynamic array is known at run time.
- The extent of dimension `n` is retrieved by calling the templated member function
  `extent<n>()`. Alternatively by calling any of the non-templated member functions:
  `extent0()`, `extent1()`, `extent2()`...
- The member function `extents` returns all extents of the array as an
  `std::array<size_t, rank()>`.


# Example

```
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
    auto static_array2d = gal::sarray<float, 3, 2>();
    auto dynamic_array2d = gal::darray<int, 2>(8, 4);
    fill_and_print_array2d(static_array2d);
    fill_and_print_array2d(dynamic_array2d);
}
```
Prints:
```
10 11 12
13 14 15

10 11 12 13 14 15 16 17
18 19 20 21 22 23 24 25
26 27 28 29 30 31 32 33
34 35 36 37 38 39 40 41
```

# Construct Owning Arrays with Uninitialized Data

## Static Owning Array

An `sarray` of size `N` can be constructed similar to an `std::array`:
```
const auto N = size_t{ 10 };
auto array0 = std::array<float, N>();
auto array1 = gal::sarray<float, N>();
```
`sarray` also supports multiple dimensions:
```
const auto N = size_t{10};
const auto M = size_t{20};
const auto L = size_t{30};
auto array0 = std::array<float, N>();
auto array1 = gal::sarray<float, N>();
auto array2 = gal::sarray<float, N, M>();
auto array3 = gal::sarray<float, N, M, L>();
```
The template arguments specify the extent of each dimension.

## Dynamic Owning Array

An `darray` of size `N` can be constructed similar to an `std::vector`:
```
size_t N = 10;
auto array0 = std::vector<float>(N);
auto array1 = gal::darray<float>(N);
```
`darray` also supports multiple dimensions:
```
auto N = {10};
auto M = {20};
auto L = {30};
auto array1 = gal::darray<float>(N);
auto array2 = gal::darray<float, 1>(N);
auto array3 = gal::darray<float, 2>(N, M);
auto array4 = gal::darray<float, 3>(N, M, L);
```
The second template argument for `darray` specifies the rank, i.e. the number of
dimensions. It has a defult value of `1`. The extent of each dimension are
specified by the non-templated arguments.

## Construct Owning Arrays with Initialized Data

`sarray` can be constructed with all the data initialized to the same value,
unlike `std::array`:
```
const auto N = size_t{10};
const auto M = size_t{20};
auto value = 6.283f;
auto array1 = gal::sarray<float, N>(value);
auto array2 = gal::sarray<float, N, M>(value);
```
`darray` can also be constructed with the data initialized to the same value
similar to `std::vector`:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto value = 6.283f;
auto array1 = std::vector<float>(N, value);
auto array2 = gal::darray<float>(N, value);
auto array3 = gal::darray<float, 2>(N, M, value);
```

## Construct Owning Arrays with Copied Data

Static arrays:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
auto array0 = std::array<float, N * M>();
auto data_pointer = array0.data();
auto array1 = gal::sarray<float, N>(data_pointer);
auto array2 = gal::sarray<float, N, M>(data_pointer);
```

Dynamic arrays:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto array1 = std::vector<float>(N * M);
auto data_pointer = array1.data();
auto array2 = gal::darray<float>(N, data_pointer);
auto array3 = gal::darray<float, 2>( N, M, data_pointer);
```

## Constructing Non-owning Pointer Arrays.

Array with static size pointing to data owned by someone else:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
auto array0 = std::array<float, N * M>();
auto data_pointer = array0.data();
auto array1 = gal::sarray_ptr<float, N>(data_pointer);
auto array2 = gal::sarray_ptr<float, N, M>(data_pointer);
```
You can specify that the data pointed at should be constant in this way:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
const auto array0 = std::array<float, N * M>();
const auto data_pointer = array0.data();
auto array1 = gal::sarray_ptr<const float, N>(data_pointer);
auto array2 = gal::sarray_ptr<const float, N, M>(data_pointer);
```
Note that `const` in front of the templated type and not in front of the array.
This is similar to how you specify a pointer to a constant using
`std::shared_ptr` and `std::uniqe_ptr`.

Array with dynamic size pointing to data owned by someone else are constructed
like this:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto array1 = std::vector<float>(N * M);
auto data_pointer = array1.data();
auto array2 = gal::darray_ptr<float>(N, data_pointer);
auto array3 = gal::darray_ptr<float, 2>(N, M, data_pointer);
```
Dynamic arrays pointing at constant data are constructed like this:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
const auto array1 = std::vector<float>(N * M);
const auto data_pointer = array1.data();
auto array2 = gal::darray_ptr<const float>(N, data_pointer);
auto array3 = gal::darray_ptr<const float, 2>(N, M, data_pointer);
```
*/

#pragma once

#include "sarray.hpp"
#include "darray.hpp"
#include "sarray_ptr.hpp"
#include "darray_ptr.hpp"

#include "vector_math.hpp"
#include "geometry.hpp"
