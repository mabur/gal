#pragma once

#include <array>
#include <valarray>
#include <vector>

template<size_t RANK>
using extents_t = std::array<size_t, RANK>;

////////////////////////////////////////////////////////////////////////////////
// Define data end extents for std arrays.

template<typename T>       T* data(      std::vector<T>& x) { return x.data(); }
template<typename T> const T* data(const std::vector<T>& x) { return x.data(); }

template<typename T>       T* data(      std::valarray<T>& x) { return std::begin(x); }
template<typename T> const T* data(const std::valarray<T>& x) { return std::begin(x); }

template<typename T, size_t N>       T* data(      std::array<T, N>& x) { return x.data(); }
template<typename T, size_t N> const T* data(const std::array<T, N>& x) { return x.data(); }

template<typename T>           extents_t<1> extents(const std::vector<T>&   a) { return extents_t<1>{a.size()}; }
template<typename T>           extents_t<1> extents(const std::valarray<T>& a) { return extents_t<1>{a.size()}; }
template<typename T, size_t N> extents_t<1> extents(const std::array<T, N>& a) { return extents_t<1>{a.size()}; }

////////////////////////////////////////////////////////////////////////////////
// Forward declare data and extents functions for the arrays.

template<typename T, size_t RANK> class darray;
template<typename T, size_t D> T* data(darray<T, D>& a);
template<typename T, size_t D> const T* data(const darray<T, D>& a);
template<typename T, size_t D> extents_t<D> extents(const darray<T, D>& a);

template<typename T, size_t RANK> class darray_ptr;
template<typename T, size_t D> T* data(darray_ptr<T, D>& a);
template<typename T, size_t D> const T* data(const darray_ptr<T, D>& a);
template<typename T, size_t D> extents_t<D> extents(const darray_ptr<T, D>& a);

template<typename T, size_t... EXTENTS> class sarray;
template<typename T, size_t... EXTENTS> T* data(sarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> const T* data(const sarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> constexpr extents_t<sizeof...(EXTENTS)> extents(const sarray<T, EXTENTS...>& a);

template<typename T, size_t... EXTENTS> class sarray_ptr;
template<typename T, size_t... EXTENTS> T* data(sarray_ptr<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> const T* data(const sarray_ptr<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> constexpr extents_t<sizeof...(EXTENTS)> extents(const sarray_ptr<T, EXTENTS...>& a);
