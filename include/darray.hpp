#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <tuple>
#include <valarray>

#include "non_member_functions.hpp"
#include "utilities.hpp"

namespace gal
{

/**
\brief An array with size known at run-time.

## Construction with Uninitialized Data

An `darray` of size `N` can be constructed similar to an `std::vector`:
```
size_t N = 10;
auto array0 = std::vector<float>(N);
auto array1 = gal::darray<float>(N);
```
`darray` also supports multiple dimensions:
```
size_t N = 10;
size_t M = 20;
size_t L = 30;
auto array1 = gal::darray<float>(N);
auto array2 = gal::darray<float, 1>(N);
auto array3 = gal::darray<float, 2>(N, M);
auto array4 = gal::darray<float, 3>(N, M, L);
```
The second template argument for `darray` specifies the rank, i.e. the number of
dimensions. It has a defult value of `1`. The extent of each dimension are
specified by the non-templated arguments.

## Construction with Initialized Data

`darray` can also be constructed with the data initialized to the same value
similar to `std::vector`:
```
size_t N = 10;
size_t M = 20;
float value = 6.283f;
auto array1 = std::vector<float>(N, value);
auto array2 = gal::darray<float>(N, value);
auto array3 = gal::darray<float, 2>(N, M, value);
```

## Construction with Copied Data

```
size_t N = 10;
size_t M = 20;
auto array1 = std::vector<float>(N * M);
auto pointer = array1.data();
auto array2 = gal::darray<float>(N, pointer);
auto array3 = gal::darray<float, 2>( N, M, pointer);
```

*/
template<typename T, size_t RANK = 1>
class darray
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
    using extents_type    = std::array<size_t, RANK>;
//  ____________________________________________________________________________
//  These are the same for all dynamic arrays in gal:
public:
    static constexpr size_t rank() { return RANK; }
    extents_type extents() const   { return extents_; }
    template<size_t DIMENSION> size_t extent() const { return extents_[DIMENSION]; }

    size_t extent0() const { return extent<0>(); }
    size_t extent1() const { return extent<1>(); }
    size_t extent2() const { return extent<2>(); }
    size_t extent3() const { return extent<3>(); }
    size_t extent4() const { return extent<4>(); }
    size_t extent5() const { return extent<5>(); }
    size_t extent6() const { return extent<6>(); }
    size_t extent7() const { return extent<7>(); }
    size_t extent8() const { return extent<8>(); }
    size_t extent9() const { return extent<9>(); }
private:
    extents_type extents_;
//  ____________________________________________________________________________
//  darray specifics:
public:
    darray<T, RANK>& operator=(const darray<T, RANK>&)  = default;
    darray<T, RANK>& operator=(      darray<T, RANK>&&) = default;

    darray(const darray<T, RANK>&)  = default;
    darray(      darray<T, RANK>&&) = default;

    darray() { std::fill(std::begin(extents_), std::end(extents_), 0); }

    template<typename Array, typename Array::value_type* = nullptr>
    explicit darray(const Array& array)
        : extents_(::extents(array))
        , data_(array.size())
    {
        std::copy(std::begin(array), std::end(array), std::begin(data_));
    }

    template<typename ... Types, typename std::enable_if<sizeof...(Types)==RANK>::type* = nullptr>
    explicit darray(Types... arguments_pack)
    {
        extents_type arguments_array{ arguments_pack... };
        extents_ = arguments_array;
        data_.resize(details::product(extents_));
    }

    template<typename ... Types, typename std::enable_if<sizeof...(Types) == RANK+1>::type* = nullptr>
    explicit darray(Types... arguments_pack)
    {
        construction_helper<0>(arguments_pack...);
        data_.resize(details::product(extents_));
    }

private:
    template<size_t i, typename ... Types>
    void construction_helper(size_t argument, Types... arguments)
    {
        extents_[i] = argument;
        construction_helper<i + 1>(arguments...);
    }

    template<size_t i>
    void construction_helper(const_reference value)
    {
        std::fill(begin(), end(), value);
        static_assert(i == RANK, "Wrong number of arguments.");
    }

    template<size_t i>
    void construction_helper(const_pointer data_pointer)
    {
        std::copy(data_pointer, data_pointer + RANK, data());
        static_assert(i == RANK, "Wrong number of arguments.");
    }
public:
    size_t size() const { return data_.size(); };
    
    T*       begin()       {return std::begin(data_);};
    const T* begin() const {return std::begin(data_);};

    T*       end()         {return std::end(data_);};
    const T* end()   const {return std::end(data_);};

    T*       data()        {return std::begin(data_);};
    const T* data()  const {return std::begin(data_);};

    T& operator[](size_t i)
    {
        assert(i < size());
        return data_[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i < size());
        return data_[i];
    }

    template<typename ... INDICES>
    T& operator()(INDICES ... indices) { return details::index(*this, indices...); }

    template<typename ... INDICES>
    const T& operator()(INDICES ... indices) const { return details::index(*this, indices...); }

private:
    std::valarray<T> data_;
};

template<typename T, size_t D> T*               data(      darray<T, D>& a) { return a.data(); }
template<typename T, size_t D> const T*         data(const darray<T, D>& a) { return a.data(); }
template<typename T, size_t D> T*              begin(      darray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> const T*        begin(const darray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> T*                end(      darray<T, D>& a) { return a.end(); }
template<typename T, size_t D> const T*          end(const darray<T, D>& a) { return a.end(); }
template<typename T, size_t D> size_t           size(const darray<T, D>& a) { return a.size(); }
template<typename T, size_t D> constexpr size_t rank(const darray<T, D>& a) { return a.rank(); }
template<typename T, size_t D> extents_t<D>  extents(const darray<T, D>& a) { return a.extents(); }
template<typename T, size_t D> size_t         extent(const darray<T, D>& a) { return a.extent<D>(); }
template<typename T, size_t D> size_t        extent0(const darray<T, D>& a) { return a.extent0(); }
template<typename T, size_t D> size_t        extent1(const darray<T, D>& a) { return a.extent1(); }
template<typename T, size_t D> size_t        extent2(const darray<T, D>& a) { return a.extent2(); }
template<typename T, size_t D> size_t        extent3(const darray<T, D>& a) { return a.extent3(); }
template<typename T, size_t D> size_t        extent4(const darray<T, D>& a) { return a.extent4(); }
template<typename T, size_t D> size_t        extent5(const darray<T, D>& a) { return a.extent5(); }
template<typename T, size_t D> size_t        extent6(const darray<T, D>& a) { return a.extent6(); }
template<typename T, size_t D> size_t        extent7(const darray<T, D>& a) { return a.extent7(); }
template<typename T, size_t D> size_t        extent8(const darray<T, D>& a) { return a.extent8(); }
template<typename T, size_t D> size_t        extent9(const darray<T, D>& a) { return a.extent9(); }

} // namespace gal
