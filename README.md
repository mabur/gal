# General Array Library
GAL is a C++ library that implements four different array classes:
* `sarray`. Container that represents a static array. The size of the array is known at compile time. Similar to `std::array`, but also supports multiple dimensions.
* `darray`. Container that represents a dynamic array. The size of the array is known at runtime. Similar to `std::vector`, but also supports multiple dimensions.
* `psarray`. Non owning pointer/view to a static array. The size of the array pointed at is known at compile time.
* `pdarray`. Non owning pointer/view to a dynamic array. The size of the array pointed at is known at runtime. Similar to `gsl::span`, but also supports multiple dimensions.

The library provides a consistent interface for all these different cases of arrays.

```
        | Owns Memory    Non Owning Pointer 
--------|----------------------------------
Static  | sarray         psarray
Dynamic | darray         pdarray
```
