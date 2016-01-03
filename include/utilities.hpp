#pragma once

// TODO:
//template<typename Array>
//T* data(Array& array);

template<typename Array>
std::array<size_t, 1> extents(const Array& a) { return std::array<size_t, 1>{a.size()}; }

template<size_t size> inline size_t product(const size_t* array);

template<> inline
size_t product<0>(const size_t*)
{
    return 1;
}

template<size_t size> inline
size_t product(const size_t* array)
{
    return array[0] * product<size - 1>(array + 1);
}


template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
	T,
	std::conditional_t<
	false,
	is_container_helper<
	//typename T::value_type,
	//typename T::size_type,
	//typename T::allocator_type,
	//typename T::iterator,
	//typename T::const_iterator,
	decltype(std::declval<T>().size()),
	decltype(std::declval<T>().begin()),
	decltype(std::declval<T>().end())//,
	//decltype(std::declval<T>().cbegin()),
	//decltype(std::declval<T>().cend())
	>,
	void
	>
> : public std::true_type{};