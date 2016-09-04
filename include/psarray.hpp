#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <tuple>

#include "utilities.hpp"
#include "non_member_functions.hpp"

/**
\brief Pointer to a static array.
*/
template<typename T, size_t... EXTENTS>
class psarray
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
//  psarray specifics:
public:

	psarray() : data_(nullptr) {}

    psarray(const psarray<T, EXTENTS...>&) = default;

    psarray<T, EXTENTS...>& operator=(const psarray<T, EXTENTS...>&) = default;

	explicit psarray(T* data) : data_(data) {}

    template<typename S>
    explicit psarray(const psarray<S, EXTENTS...>& array)
        : data_(array.data())
    {}

	template<typename Array, typename Array::value_type* = nullptr>
	explicit psarray(Array& array)
		: data_(::data(array))
	{
		assert(array.size() == size());
	}

    template<typename Array, typename Array::value_type* = nullptr>
    explicit psarray(const Array& array)
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

template<typename T, size_t... EXTENTS> T*        data(psarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> const T*  data(const psarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> T*       begin(psarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const psarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(psarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> const T*   end(const psarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> size_t    size(const psarray<T, EXTENTS...>& a) { return a.size(); }

template<typename T, size_t... EXTENTS> extents_t<sizeof...(EXTENTS)> extents(const psarray<T, EXTENTS...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const psarray<T, W, H>& a) { return a.rank(); }
