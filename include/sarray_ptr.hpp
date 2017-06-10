#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <tuple>

#include "utilities.hpp"
#include "non_member_functions.hpp"

namespace gal
{

/**
\brief \brief A non-owning pointer to an array with size known at compile-time.

## Construction

Construction of arrays pointing to data owned by someone else:
```
const size_t N = 10;
const size_t M = 20;
auto array0 = std::array<float, N * M>();
auto pointer = array0.data();
auto array1 = gal::sarray_ptr<float, N>(pointer);
auto array2 = gal::sarray_ptr<float, N, M>(pointer);
```
You can specify that the data pointed at should be constant in this way:
```
const size_t N = 10;
const size_t M = 20;
const auto array0 = std::array<float, N * M>();
const auto pointer = array0.data();
auto array1 = gal::sarray_ptr<const float, N>(pointer);
auto array2 = gal::sarray_ptr<const float, N, M>(pointer);
```
Note that `const` in front of the templated type and not in front of the array.
This is similar to how you specify a pointer to a constant using
`std::shared_ptr` and `std::uniqe_ptr`.

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
//  ____________________________________________________________________________
//  sarray_ptr specifics:
public:

    sarray_ptr<T, EXTENTS...>& operator=(const sarray_ptr<T, EXTENTS...>&)  = default;
    sarray_ptr<T, EXTENTS...>& operator=(      sarray_ptr<T, EXTENTS...>&&) = default;

    sarray_ptr(const sarray_ptr<T, EXTENTS...>&)  = default;
    sarray_ptr(      sarray_ptr<T, EXTENTS...>&&) = default;

    sarray_ptr() : data_(nullptr) {}

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

} // namespace gal
