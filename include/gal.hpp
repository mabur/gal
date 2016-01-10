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

All of these arrays support multiple dimensions.

# Other standard arrays

The standard template library [STL](http://www.cplusplus.com/reference/stl/),
and the Guidelines Support Library [GSL](https://github.com/Microsoft/GSL), also
contain some array classes:
```
        | Owns Memory    Non Owning Pointer
--------|----------------------------------
Static  | std::array     -
Dynamic | std::vector    gsl::span
        | std::valarray
```
Note that these do not support multiple dimensions.

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

*/

#pragma once

#include "sarray.hpp"
#include "darray.hpp"
#include "psarray.hpp"
#include "pdarray.hpp"

#include "vector_math.hpp"
#include "geometry.hpp"
