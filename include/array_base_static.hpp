#pragma once

#include <algorithm>
#include <array>
#include <tuple>

#include "array_base.hpp"
#include "utilities.hpp"

/**
\brief The base class that all static arrays derive from,
i.e. arrays with size known at compile-time. Defines size and extents for such arrays.
*/
template<typename T, size_t... EXTENTS>
class array_base_static : public array_base<T, sizeof...(EXTENTS)>
{
public:
    using typename array_base<T, sizeof...(EXTENTS)>::extents_type;

	static constexpr size_t size() { return details::total_size<EXTENTS...>::value; };

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
};
