#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>

#include "non_member_functions.hpp"
#include "utilities.hpp"

namespace gal
{

/**
\brief A non-owning pointer to an array with size known at run-time.
*/
template<typename T, size_t RANK = 1>
class darray_ptr
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
//  darray_ptr specifics:
public:
    darray_ptr<T, RANK>& operator=(const darray_ptr<T, RANK>&)  = default;
    darray_ptr<T, RANK>& operator=(      darray_ptr<T, RANK>&&) = default;

    darray_ptr(const darray_ptr<T, RANK>&)  = default;
    darray_ptr(      darray_ptr<T, RANK>&&) = default;

    darray_ptr() : data_(nullptr), size_(0)
    {
        std::fill(std::begin(extents_), std::end(extents_), 0);
    }    

    template<typename ... Types, typename std::enable_if<sizeof...(Types) == RANK + 1>::type* = nullptr>
    explicit darray_ptr(Types... arguments_pack)
    {
        construction_helper<0>(arguments_pack...);
        size_ = details::product(extents_);
        assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    template<typename S>
    explicit darray_ptr(const darray_ptr<S, RANK>& array)
        : extents_(array.extents())
        , data_(array.data())
        , size_(array.size())
    {
        assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    template<typename Array>
    explicit darray_ptr(Array& array)
        : extents_(::extents(array))
        , data_(::data(array))
        , size_(array.size())
    {
        assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    template<typename Array>
    explicit darray_ptr(const Array& array)
        : extents_(::extents(array))
        , data_(::data(array))
        , size_(array.size())
    {
        assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }
private:
    template<size_t i, typename ... Types>
    void construction_helper(size_t argument, Types... arguments)
    {
        extents_[i] = argument;
        construction_helper<i + 1>(arguments...);
    }

    template<size_t i>
    void construction_helper(pointer data_pointer)
    {
        data_ = data_pointer;
        static_assert(i == RANK, "Wrong number of arguments.");
    }
public:
    inline size_t size() const { return size_; }
    inline T* begin()    const { return data_; }
    inline T* end()      const { return data_ + size_; }
    inline T* data()     const { return data_; }

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
    size_t size_;
};

template<typename T, size_t D> T*               data      (darray_ptr<T, D>& a) { return a.data(); }
template<typename T, size_t D> const T*         data(const darray_ptr<T, D>& a) { return a.data(); }
template<typename T, size_t D> T*              begin(      darray_ptr<T, D>& a) { return a.begin(); }
template<typename T, size_t D> const T*        begin(const darray_ptr<T, D>& a) { return a.begin(); }
template<typename T, size_t D> T*                end(      darray_ptr<T, D>& a) { return a.end(); }
template<typename T, size_t D> const T*          end(const darray_ptr<T, D>& a) { return a.end(); }
template<typename T, size_t D> size_t           size(const darray_ptr<T, D>& a) { return a.size(); }
template<typename T, size_t D> constexpr size_t rank(const darray_ptr<T, D>& a) { return a.rank(); }
template<typename T, size_t D> extents_t<D>  extents(const darray_ptr<T, D>& a) { return a.extents(); }
template<typename T, size_t D> size_t         extent(const darray_ptr<T, D>& a) { return a.extent<D>(); }
template<typename T, size_t D> size_t        extent0(const darray_ptr<T, D>& a) { return a.extent0(); }
template<typename T, size_t D> size_t        extent1(const darray_ptr<T, D>& a) { return a.extent1(); }
template<typename T, size_t D> size_t        extent2(const darray_ptr<T, D>& a) { return a.extent2(); }
template<typename T, size_t D> size_t        extent3(const darray_ptr<T, D>& a) { return a.extent3(); }
template<typename T, size_t D> size_t        extent4(const darray_ptr<T, D>& a) { return a.extent4(); }
template<typename T, size_t D> size_t        extent5(const darray_ptr<T, D>& a) { return a.extent5(); }
template<typename T, size_t D> size_t        extent6(const darray_ptr<T, D>& a) { return a.extent6(); }
template<typename T, size_t D> size_t        extent7(const darray_ptr<T, D>& a) { return a.extent7(); }
template<typename T, size_t D> size_t        extent8(const darray_ptr<T, D>& a) { return a.extent8(); }
template<typename T, size_t D> size_t        extent9(const darray_ptr<T, D>& a) { return a.extent9(); }

} // namespace gal
