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
