#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <tuple>

#include "utilities.hpp"
#include "non_member_functions.hpp"

/**
\brief \brief A non-owning pointer to an array with size known at compile-time.
*/
template<typename T, size_t... EXTENTS>
class sarray_ptr
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

    static constexpr size_t extent0() { return extent<0>(); }
    static constexpr size_t extent1() { return extent<1>(); }
    static constexpr size_t extent2() { return extent<2>(); }
    static constexpr size_t extent3() { return extent<3>(); }
    static constexpr size_t extent4() { return extent<4>(); }
    static constexpr size_t extent5() { return extent<5>(); }
    static constexpr size_t extent6() { return extent<6>(); }
    static constexpr size_t extent7() { return extent<7>(); }
    static constexpr size_t extent8() { return extent<8>(); }
    static constexpr size_t extent9() { return extent<9>(); }
//  ____________________________________________________________________________
//  sarray_ptr specifics:
public:

    sarray_ptr() : data_(nullptr) {}

    sarray_ptr(const sarray_ptr<T, EXTENTS...>&) = default;

    sarray_ptr<T, EXTENTS...>& operator=(const sarray_ptr<T, EXTENTS...>&) = default;

    explicit sarray_ptr(T* data) : data_(data) {}

    template<typename S>
    explicit sarray_ptr(const sarray_ptr<S, EXTENTS...>& array)
        : data_(array.data())
    {}

    template<typename Array, typename Array::value_type* = nullptr>
    explicit sarray_ptr(Array& array)
        : data_(::data(array))
    {
        assert(array.size() == size());
    }

    template<typename Array, typename Array::value_type* = nullptr>
    explicit sarray_ptr(const Array& array)
        : data_(::data(array))
    {
        assert(array.size() == size());
    }

    inline T* begin() const { return data_; }
    inline T* end()   const { return data_ + size(); }
    inline T* data()  const { return data_; }

    inline T& operator[](size_t i) const
    {
        assert(i < size());
        return data_[i];
    }

    template<typename ... INDICES>
    T& operator()(INDICES ... indices) { return details::index(*this, indices...); }

    template<typename ... INDICES>
    const T& operator()(INDICES ... indices) const { return details::index(*this, indices...); }

private:
    T* data_;
};

template<typename T, size_t... EXTENTS> T*        data(      sarray_ptr<T, EXTENTS...>& a) { return a.data();  }
template<typename T, size_t... EXTENTS> const T*  data(const sarray_ptr<T, EXTENTS...>& a) { return a.data();  }
template<typename T, size_t... EXTENTS> T*       begin(      sarray_ptr<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const sarray_ptr<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(      sarray_ptr<T, EXTENTS...>& a) { return a.end();   }
template<typename T, size_t... EXTENTS> const T*   end(const sarray_ptr<T, EXTENTS...>& a) { return a.end();   }
template<typename T, size_t... EXTENTS> size_t    size(const sarray_ptr<T, EXTENTS...>& a) { return a.size();  }

template<          typename T, size_t... EXTENTS> constexpr size_t                           rank(const sarray_ptr<T, EXTENTS...>& a) { return a.rank(); }
template<          typename T, size_t... EXTENTS> constexpr extents_t<sizeof...(EXTENTS)> extents(const sarray_ptr<T, EXTENTS...>& a) { return a.extents(); }
template<size_t D, typename T, size_t... EXTENTS> constexpr size_t                         extent(const sarray_ptr<T, EXTENTS...>& a) { return a.extent<D>(); }

template<typename T, size_t... EXTENTS> constexpr size_t extent0(const sarray_ptr<T, EXTENTS...>& a) { return a.extent0(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent1(const sarray_ptr<T, EXTENTS...>& a) { return a.extent1(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent2(const sarray_ptr<T, EXTENTS...>& a) { return a.extent2(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent3(const sarray_ptr<T, EXTENTS...>& a) { return a.extent3(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent4(const sarray_ptr<T, EXTENTS...>& a) { return a.extent4(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent5(const sarray_ptr<T, EXTENTS...>& a) { return a.extent5(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent6(const sarray_ptr<T, EXTENTS...>& a) { return a.extent6(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent7(const sarray_ptr<T, EXTENTS...>& a) { return a.extent7(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent8(const sarray_ptr<T, EXTENTS...>& a) { return a.extent8(); }
template<typename T, size_t... EXTENTS> constexpr size_t extent9(const sarray_ptr<T, EXTENTS...>& a) { return a.extent9(); }
