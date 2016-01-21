/** \mainpage

# Overview of GAL

This library consists of four different array classes:
```
        | Owns Memory    Non Owning Pointer
--------|----------------------------------
Static  | sarray         psarray
Dynamic | darray         pdarray
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

# Other standard arrays

The standard template library [STL](http://www.cplusplus.com/reference/stl/) has
some array containers:
```
        | Owns Memory    Non Owning Pointer
--------|----------------------------------
Static  | std::array     -
Dynamic | std::vector    -
        | std::valarray
```
STL has no class for multi-dimensional arrays or any class for
representing non owning pointers to general arrays.
The Guidelines Support Library [GSL](https://github.com/Microsoft/GSL) has a
class that represents a non owning pointer to a single-dimensional dynamic array:
```
        | Owns Memory    Non Owning Pointer
--------|----------------------------------
Static  | -              -
Dynamic | -              gsl::span
```
[The Boost Multidimensional Array Library]
(http://www.boost.org/doc/libs/1_60_0/libs/multi_array/doc/index.html)
has support for multi-dimensional dynamic arrays:
```
        | Owns Memory    Non Owning Pointer
--------|----------------------------------
Static  | -              -
Dynamic | multi_array    multi_array_ref
        |                const_multi_array_ref
```
GAL attempts to fill in the gaps between these libraries and at the same time
provide a consistent interface.


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


# Construct Owning Arrays with Uninitialized Data

## Static Owning Array

An `sarray` of size `N` can be constructed similar to an `std::array`:
```
const auto N = size_t{ 10 };
auto array0 = std::array<float, N>();
auto array1 = sarray<float, N>();
```
`sarray` also supports multiple dimensions:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
const auto L = size_t{ 30 };
auto array0 = std::array<float, N>();
auto array1 = sarray<float, N>();
auto array2 = sarray<float, N, M>();
auto array3 = sarray<float, N, M, L>();
```
The template arguments specify the extent of each dimension.

## Dynamic Owning Array

An `darray` of size `N` can be constructed similar to an `std::vector`:
```
auto N = size_t{ 10 };
auto array0 = std::vector<float>(N);
auto array1 = darray<float>(N);
```
`darray` also supports multiple dimensions:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto L = size_t{ 30 };
auto array1 = darray<float, 1>({ N });
auto array1 = darray<float, 2>({ N, M });
auto array1 = darray<float, 3>({ N, M, L });
```
The second template argument for `darray` specifies the rank, i.e. the number of
dimensions. It has a defult value of `1`. The extent of each dimension are
specified by the non-templated argument. For `darray` of rank 1 the braces
around the extent is optional and all of these have the same meaning:
```
auto N = size_t{ 10 };
auto array0 = darray<float>(N);
auto array1 = darray<float>({N});
auto array2 = darray<float, 1>(N);
auto array3 = darray<float, 1>({N});
```

## Construct Owning Arrays with Initialized Data

`sarray` can be constructed with all the data initialized to the same value,
unlike `std::array`:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
auto value = 6.283f;
auto array1 = sarray<float, N>(value);
auto array2 = sarray<float, N, M>(value);
```
`darray` can also be constructed with the data initialized to the same value
similar to `std::vector`:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto value = 6.283f;
auto array1 = std::vector<float>(N, value);
auto array2 = darray<float>({ N }, value); // TODO: allow without braces.
auto array3 = darray<float, 2>({ N, M }, value);
```

## Construct Owning Arrays with Copied Data

Static arrays:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
auto array0 = std::array<float, N * M>();
auto data_pointer = array0.data();
auto array1 = sarray<float, N>(data_pointer);
auto array2 = sarray<float, N, M>(data_pointer);
```

Dynamic arrays:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto array1 = std::vector<float>(N * M);
auto data_pointer = array1.data();
auto array2 = darray<float>(N, data_pointer);
auto array3 = darray<float, 2>({ N, M }, data_pointer);
```

## Constructing Non-owning Pointer Arrays.

Array with static size pointing to data owned by someone else:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
auto array0 = std::array<float, N * M>();
auto data_pointer = array0.data();
auto array1 = psarray<float, N>(data_pointer);
auto array2 = psarray<float, N, M>(data_pointer);
```
You can specify that the data pointed at should be constant in this way:
```
const auto N = size_t{ 10 };
const auto M = size_t{ 20 };
const auto array0 = std::array<float, N * M>();
const auto data_pointer = array0.data();
auto array1 = psarray<const float, N>(data_pointer);
auto array2 = psarray<const float, N, M>(data_pointer);
```
Note that `const` in front of the templated type and not in front of the array.
This is similar to how you specofy a pointer to a constant using
`std::shared_ptr` and `std::uniqe_ptr`.

Array with dynamic size pointing to data owned by someone else are constructed
like this:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
auto array1 = std::vector<float>(N * M);
auto data_pointer = array1.data();
auto array2 = pdarray<float>(N, data_pointer);
auto array3 = pdarray<float, 2>({ N, M }, data_pointer);
```
Dynamic arrays pointing at constant data are constructed like this:
```
auto N = size_t{ 10 };
auto M = size_t{ 20 };
const auto array1 = std::vector<float>(N * M);
const auto data_pointer = array1.data();
auto array2 = pdarray<const float>(N, data_pointer);
auto array3 = pdarray<const float, 2>({ N, M }, data_pointer);
```
*/



#pragma once

#include "sarray.hpp"
#include "darray.hpp"
#include "psarray.hpp"
#include "pdarray.hpp"

#include "vector_math.hpp"
#include "geometry.hpp"
