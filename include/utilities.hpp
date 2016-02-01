#pragma once

namespace details
{

template<typename Array>
size_t offset(const Array&)
{
    return 0;
}

template<typename Array, typename ... INDICES>
size_t offset(const Array& a, size_t index, INDICES ... indices)
{
    constexpr auto e = Array::rank() - 1 - sizeof...(indices);
    return index + a.template extent<e>() * offset(a, indices...);
}

template<typename Array, typename ... INDICES>
typename Array::const_reference index(const Array& a, INDICES ... indices)
{
    return a[offset(a, indices ...)];
}

template<typename Array, typename ... INDICES>
typename Array::reference index(Array& a, INDICES ... indices)
{
    return a[offset(a, indices ...)];
}

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

template<size_t size> inline
size_t product(const std::array<size_t, size>& array)
{
    return product<size>(&array.front());
}

template<size_t size, size_t... sizes>
struct total_size
{
    static constexpr size_t value = size * total_size<sizes...>::value;
};

template<size_t size>
struct total_size<size>
{
    static constexpr size_t value = size;
};

} // namespace details