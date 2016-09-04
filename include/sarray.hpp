#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <initializer_list>

#include "utilities.hpp"
#include "non_member_functions.hpp"

/**
\brief Static array.
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
//  sarray specifics:
public:
	sarray() = default;

    sarray(const sarray<T, EXTENTS...>&) = default;

    sarray<T, EXTENTS...>& operator=(const sarray<T, EXTENTS...>&) = default;

	//explicit sarray(const std::array<T, total_size<EXTENTS...>::value>& data)
	//	: data_(data)
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

	explicit sarray(const T* data_begin)
	{
		std::copy(data_begin, data_begin + size(), std::begin(data_));
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

template<typename T, size_t... EXTENTS> T*        data(      sarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> const T*  data(const sarray<T, EXTENTS...>& a) { return a.data(); }
template<typename T, size_t... EXTENTS> T*       begin(      sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> const T* begin(const sarray<T, EXTENTS...>& a) { return a.begin(); }
template<typename T, size_t... EXTENTS> T*         end(      sarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> const T*   end(const sarray<T, EXTENTS...>& a) { return a.end(); }
template<typename T, size_t... EXTENTS> size_t    size(const sarray<T, EXTENTS...>& a) { return a.size(); }

template<typename T, size_t... EXTENTS> extents_t<sizeof...(EXTENTS)> extents(const sarray<T, EXTENTS...>& a) { return a.extents(); }

template<typename T, size_t W, size_t H> constexpr size_t rank(const sarray<T, W, H>& a) {return a.rank();}
