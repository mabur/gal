#pragma once

#include "array_base_dynamic.hpp"

/**
\brief Pointer to a dynamic array.
*/
template<typename T, size_t D = 1>
class pdarray : public array_base_dynamic<T, D>
{
public:

    pdarray() : data_(nullptr), size_(0) {}

	pdarray(const Extents& extents, T* data)
		: array_base_dynamic(extents)
		, data_(data)
		, size_(array_base_dynamic::size())
	{
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
	}

	pdarray(size_t size, T* data)
		: array_base_dynamic({size})
		, data_(data)
		, size_(size)
	{
		static_assert(RANK == 1, "Wrong rank");
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
	}

    template<typename Array>
    explicit pdarray(Array& array)
		: array_base_dynamic(::extents(array))
		, data_(std::data(array))
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    template<typename Array>
    explicit pdarray(const Array& array)
		: array_base_dynamic(::extents(array))
		, data_(std::data(array))
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    inline T* begin()    const { return data_; }
    inline T* end()      const { return data_ + size_; }
    inline T* data()     const { return data_; }
    inline size_t size() const { return size_; }

    inline T& operator[](size_t i) const
    {
        assert(i < size());
        return data_[i];
    }

	T& operator()(size_t i0)                       { return get_element(*this, i0); }
	T& operator()(size_t i0, size_t i1)            { return get_element(*this, i0, i1); }
	T& operator()(size_t i0, size_t i1, size_t i2) { return get_element(*this, i0, i1, i2); }

	const T& operator()(size_t i0)                       const { return get_element(*this, i0); }
	const T& operator()(size_t i0, size_t i1)            const { return get_element(*this, i0, i1); }
	const T& operator()(size_t i0, size_t i1, size_t i2) const { return get_element(*this, i0, i1, i2); }

private:
    T* data_;
    size_t size_;
};

template<typename T, size_t D> T*        data(pdarray<T, D>& a)       { return a.data(); }
template<typename T, size_t D> const T*  data(const pdarray<T, D>& a) { return a.data(); }
template<typename T, size_t D> T*       begin(pdarray<T, D>& a)       { return a.begin(); }
template<typename T, size_t D> const T* begin(const pdarray<T, D>& a) { return a.begin(); }
template<typename T, size_t D> T*         end(pdarray<T, D>& a)       { return a.end(); }
template<typename T, size_t D> const T*   end(const pdarray<T, D>& a) { return a.end(); }
template<typename T, size_t D> size_t    size(const pdarray<T, D>& a) { return a.size(); }

template<typename T, size_t D> constexpr size_t rank(const pdarray<T, D>& a) { return a.rank(); }

template<typename T, size_t D> std::array<size_t, D> extents(const pdarray<T, D>& a) { return a.extents(); }
