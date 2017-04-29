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
            // Access array data with multi-dimensional index, using operator()
            cout << array(x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
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
}
```
Prints:
```
Data of owning arrays:
10 11 12
13 14 15
16 17 18

10 11 12 13
14 15 16 17
18 19 20 21
22 23 24 25

Data pointed to by non-owning arrays:
10 11 12
13 14 15

10 11 12 13
14 15 16 17
```

Please see the page for each class for more exampels and details:
gal::sarray, gal::sarray_ptr, gal::darray, gal::darray_ptr.

*/

#pragma once

#include "sarray.hpp"
#include "darray.hpp"
#include "sarray_ptr.hpp"
#include "darray_ptr.hpp"
