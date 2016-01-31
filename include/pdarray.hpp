#pragma once

#include <cassert>

#include "array_base_dynamic.hpp"

/**
\brief Pointer to a dynamic array.
*/
template<typename T, size_t RANK = 1>
class pdarray : public array_base_dynamic<T, RANK>
{
public:

    using typename array_base<T, RANK>::extents_type;

    pdarray() : data_(nullptr), size_(0) {}

	pdarray(const extents_type& extents, T* data)
		: array_base_dynamic<T, RANK>(extents)
		, data_(data)
		, size_(product(extents))
	{
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
	}

	pdarray(size_t size, T* data)
		: array_base_dynamic<T, RANK>({size})
		, data_(data)
		, size_(size)
	{
		static_assert(RANK == 1, "Wrong rank");
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
	}

    template<typename Array>
    explicit pdarray(Array& array)
		: array_base_dynamic<T, RANK>(::extents(array))
		, data_(std::data(array))
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    template<typename Array>
    explicit pdarray(const Array& array)
		: array_base_dynamic<T, RANK>(::extents(array))
		, data_(std::data(array))
		, size_(array.size())
    {
		assert(data_ != nullptr || size_ == 0); // Keep the assert?
    }

    inline size_t size() const { return size_; }
    inline T* begin()    const { return data_; }
    inline T* end()      const { return data_ + size_; }
    inline T* data()     const { return data_; }

    inline T& operator[](size_t i) const
    {
        assert(i < size());
        return data_[i];
    }

	T& operator()(size_t i0)                       { return data_[i0]; }
	T& operator()(size_t i0, size_t i1)            { return data_[i0 + this->extent0() * i1]; }
    T& operator()(size_t i0, size_t i1, size_t i2) { return data_[i0 + this->extent0() * (i1 + this->extent1() * i2)]; }

	const T& operator()(size_t i0)                       const { return data_[i0]; }
	const T& operator()(size_t i0, size_t i1)            const { return data_[i0 + this->extent0() * i1]; }
    const T& operator()(size_t i0, size_t i1, size_t i2) const { return data_[i0 + this->extent0() * (i1 + this->extent1() * i2)]; }

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
