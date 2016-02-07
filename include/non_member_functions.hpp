#pragma once

#include <array>
#include <valarray>
#include <vector>

template<typename T>       T* data(      std::vector<T>& x) { return x.data(); }
template<typename T> const T* data(const std::vector<T>& x) { return x.data(); }

template<typename T>       T* data(      std::valarray<T>& x) { return std::begin(x); }
template<typename T> const T* data(const std::valarray<T>& x) { return std::begin(x); }

template<typename T, size_t N>       T* data(      std::array<T, N>& x) { return x.data(); }
template<typename T, size_t N> const T* data(const std::array<T, N>& x) { return x.data(); }

// TODO:
//template<typename Array>
//T* data(Array& array);

template<typename Array>
std::array<size_t, 1> extents(const Array& a) { return std::array<size_t, 1>{a.size()}; }

// Forward declare data and extents functions for the arrays:

template<typename T, size_t RANK> class darray;
template<typename T, size_t D> T* data(darray<T, D>& a);
template<typename T, size_t D> const T* data(const darray<T, D>& a);
template<typename T, size_t D> std::array<size_t, D> extents(const darray<T, D>& a);

template<typename T, size_t RANK> class pdarray;
template<typename T, size_t D> T* data(pdarray<T, D>& a);
template<typename T, size_t D> const T* data(const pdarray<T, D>& a);
template<typename T, size_t D> std::array<size_t, D> extents(const pdarray<T, D>& a);

template<typename T, size_t... EXTENTS> class sarray;
template<typename T, size_t... EXTENTS> T* data(sarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> const T* data(const sarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> std::array<size_t, sizeof...(EXTENTS)> extents(const sarray<T, EXTENTS...>& a);

template<typename T, size_t... EXTENTS> class psarray;
template<typename T, size_t... EXTENTS> T* data(psarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> const T* data(const psarray<T, EXTENTS...>& a);
template<typename T, size_t... EXTENTS> std::array<size_t, sizeof...(EXTENTS)> extents(const psarray<T, EXTENTS...>& a);
