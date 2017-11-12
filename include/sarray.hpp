#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <initializer_list>

#include "utilities.hpp"
#include "non_member_functions.hpp"

namespace gal
{

/**
\brief An array with size known at compile-time.

## Construction with Uninitialized Data

An `sarray` of size `N` can be constructed similar to an `std::array`:
```
const size_t N = 10;
auto array0 = std::array<float, N>();
auto array1 = gal::sarray<float, N>();
```
`sarray` also supports multiple dimensions:
```
const size_t N = 10;
const size_t M = 20;
const size_t L = 30;
auto array0 = std::array<float, N>();
auto array1 = gal::sarray<float, N>();
auto array2 = gal::sarray<float, N, M>();
auto array3 = gal::sarray<float, N, M, L>();
```
The template arguments specify the extent of each dimension.

## Construction with Initialized Data

`sarray` can be constructed with all the data initialized to the same value,
unlike `std::array`:
```
const size_t N = 10;
const size_t M = 20;
float value = 6.283f;
auto array1 = gal::sarray<float, N>(value);
auto array2 = gal::sarray<float, N, M>(value);
```

## Construction with Copied Data

```
const size_t N = 10;
const size_t M = 20;
auto array0 = std::array<float, N * M>();
auto pointer = array0.data();
auto array1 = gal::sarray<float, N>(pointer);
auto array2 = gal::sarray<float, N, M>(pointer);
```
*/
template<typename T, size_t... EXTENTS>
class sarray
{
//  ____________________________________________________________________________
//  These are the same for all arrays in gal:
public:
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using iterator        = T*;
    using const_iterator  = const T*;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using extents_type    = std::array<size_t, sizeof...(EXTENTS)>;
//  ____________________________________________________________________________
//  These are the same for all static arrays in gal:
private:
    static const size_t SIZE = details::total_size<EXTENTS...>::value;
    static const size_t RANK = sizeof...(EXTENTS);

public:
    static constexpr size_t size()          { return SIZE; };
    static constexpr size_t rank()          { return RANK; }
    static constexpr extents_type extents() { return{ EXTENTS... }; }

    template<size_t DIMENSION>
    static constexpr size_t extent()
    {
        return std::get<DIMENSION>(std::make_tuple(EXTENTS...));
    }
//  ____________________________________________________________________________
//  sarray specifics:
public:
    
    sarray<T, EXTENTS...>& operator=(const sarray<T, EXTENTS...>&)  = default;
    sarray<T, EXTENTS...>& operator=(      sarray<T, EXTENTS...>&&) = default;

    sarray(const sarray<T, EXTENTS...>&)  = default;
    sarray(      sarray<T, EXTENTS...>&&) = default;

    sarray() = default;

    //explicit sarray(const std::array<T, total_size<EXTENTS...>::value>& data)
    //  : data_(data)
    //{}

    explicit sarray(const std::initializer_list<T>& data)
    {
        assert(data.size() == data_.size());
        std::copy(data.begin(), data.end(), data_.begin());
    }

    explicit sarray(const T& value)
    {
        std::fill(std::begin(data_), std::end(data_), value);
    }

    template<typename Iterator, typename std::iterator_traits<Iterator>::value_type* = nullptr>
    explicit sarray(Iterator first)
    {
    }

    template<typename Array, typename Array::value_type* = nullptr>
    explicit sarray(const Array& array)
    {
        assert(array.size() == size());
        std::copy(std::begin(array), std::end(array), std::begin(data_));
    }

    T*       begin()       {return data();};
    const T* begin() const {return data();};

    T*       end()         {return data() + size();};
    const T* end()   const {return data() + size();};

    T*       data()        {return data_.data();};
    const T* data()  const {return data_.data();};

    T&       operator[](size_t i)       { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    template<typename ... INDICES>
    T& operator()(INDICES ... indices) { return details::index(*this, indices...); }

    template<typename ... INDICES>
    const T& operator()(INDICES ... indices) const { return details::index(*this, indices...); }

private:
    std::array<T, SIZE> data_;
};

template<typename T, size_t... EXTENTS> T*        data(      sarray<T, EXTENTS...>& a) { return a.data();  }
template<typename T, size_t... EXTENTS> const T*  data(const sarray<T, EXTENTS...>& a) { return a.data();  }
template<typename T, size_t... EXTENTS> T*       begin(      sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(      sarray<T, EXTENTS...>& a) { return a.end();   }
template<typename T, size_t... EXTENTS> const T*   end(const sarray<T, EXTENTS...>& a) { return a.end();   }
template<typename T, size_t... EXTENTS> size_t    size(const sarray<T, EXTENTS...>& a) { return a.size();  }

template<          typename T, size_t... EXTENTS> constexpr size_t                           rank(const sarray<T, EXTENTS...>& a) { return a.rank(); }
template<          typename T, size_t... EXTENTS> constexpr extents_t<sizeof...(EXTENTS)> extents(const sarray<T, EXTENTS...>& a) { return a.extents(); }
template<size_t D, typename T, size_t... EXTENTS> constexpr size_t                         extent(const sarray<T, EXTENTS...>& a) { return a.extent<D>(); }

} // namespace gal
