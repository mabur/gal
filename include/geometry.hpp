#pragma once

#include "sarray.hpp"
#include "vector_math.hpp"

namespace gal
{

typedef sarray<float, 1> vector1f;
typedef sarray<float, 2> vector2f;
typedef sarray<float, 3> vector3f;
typedef sarray<float, 4> vector4f;

template<typename T, size_t R, size_t C>
using matrix = sarray<T, R, C>;

//typedef sarray<float, 1, 1> matrix1f;
//typedef sarray<float, 2, 2> matrix2f;
//typedef sarray<float, 3, 3> matrix3f;
//typedef sarray<float, 4, 4> matrix4f;
//
//typedef sarray<float, 1, 1> matrix11f;
//typedef sarray<float, 1, 2> matrix21f;
//typedef sarray<float, 1, 3> matrix31f;
//typedef sarray<float, 1, 4> matrix41f;
//
//typedef sarray<float, 2, 1> matrix12f;
//typedef sarray<float, 2, 2> matrix22f;
//typedef sarray<float, 2, 3> matrix32f;
//typedef sarray<float, 2, 4> matrix42f;
//
//typedef sarray<float, 3, 1> matrix13f;
//typedef sarray<float, 3, 2> matrix23f;
//typedef sarray<float, 3, 3> matrix33f;
//typedef sarray<float, 3, 4> matrix43f;
//
//typedef sarray<float, 4, 1> matrix14f;
//typedef sarray<float, 4, 2> matrix24f;
//typedef sarray<float, 4, 3> matrix34f;
//typedef sarray<float, 4, 4> matrix44f;

template<typename T, size_t R, size_t C>
matrix<T, R, C> make_matrix(const std::array<T, C * R>& elements)
{
    auto M = matrix<T, R, C>(elements);
    size_t i = 0;
    for (size_t r = 0; r < R; ++r)
        for (size_t c = 0; c < C; ++c)
            M(r, c) = elements[i++];
    return M;
}

matrix<float, 1, 1> make_matrix11f(const std::array<float, 1 * 1>& x) { return make_matrix<float, 1, 1>(x); }
matrix<float, 1, 2> make_matrix12f(const std::array<float, 1 * 2>& x) { return make_matrix<float, 1, 2>(x); }
matrix<float, 1, 3> make_matrix13f(const std::array<float, 1 * 3>& x) { return make_matrix<float, 1, 3>(x); }
matrix<float, 1, 4> make_matrix14f(const std::array<float, 1 * 4>& x) { return make_matrix<float, 1, 4>(x); }

matrix<float, 2, 1> make_matrix21f(const std::array<float, 2 * 1>& x) { return make_matrix<float, 2, 1>(x); }
matrix<float, 2, 2> make_matrix22f(const std::array<float, 2 * 2>& x) { return make_matrix<float, 2, 2>(x); }
matrix<float, 2, 3> make_matrix23f(const std::array<float, 2 * 3>& x) { return make_matrix<float, 2, 3>(x); }
matrix<float, 2, 4> make_matrix24f(const std::array<float, 2 * 4>& x) { return make_matrix<float, 2, 4>(x); }

matrix<float, 3, 1> make_matrix31f(const std::array<float, 3 * 1>& x) { return make_matrix<float, 3, 1>(x); }
matrix<float, 3, 2> make_matrix32f(const std::array<float, 3 * 2>& x) { return make_matrix<float, 3, 2>(x); }
matrix<float, 3, 3> make_matrix33f(const std::array<float, 3 * 3>& x) { return make_matrix<float, 3, 3>(x); }
matrix<float, 3, 4> make_matrix34f(const std::array<float, 3 * 4>& x) { return make_matrix<float, 3, 4>(x); }

matrix<float, 4, 1> make_matrix41f(const std::array<float, 4 * 1>& x) { return make_matrix<float, 4, 1>(x); }
matrix<float, 4, 2> make_matrix42f(const std::array<float, 4 * 2>& x) { return make_matrix<float, 4, 2>(x); }
matrix<float, 4, 3> make_matrix43f(const std::array<float, 4 * 3>& x) { return make_matrix<float, 4, 3>(x); }
matrix<float, 4, 4> make_matrix44f(const std::array<float, 4 * 4>& x) { return make_matrix<float, 4, 4>(x); }

template<typename T, size_t R, size_t C>
size_t rows(const sarray<T, R, C>& matrix)
{
    return R;
}

template<typename T, size_t R, size_t C>
size_t columns(const sarray<T, R, C>& matrix)
{
    return C;
}

template<typename T, size_t R1, size_t C1_R2, size_t C2>
matrix<T, R1, C2> multiply(const matrix<T, R1, C1_R2>& A, const matrix<T, C1_R2, C2>& B)
{
    auto result = matrix<T, R1, C2>();
    for (size_t r = 0; r < R1; ++r)
    {
        for (size_t c = 0; c < C2; ++c)
        {
            auto element = T();
            for (size_t i = 0; i < C1_R2; ++i)
            {
                element += A(r, i) * B(i, c);
            }
            result(r, c) = element;
        }
    }
    return result;
}

// TODO: reuse in make_matrix or the other way around.
template<typename T, size_t R, size_t C>
matrix<T, C, R> transpose(const matrix<T, R, C>& in)
{
    auto out = matrix<T, C, R>();
    for (size_t r = 0; r < R; ++r)
    {
        for (size_t c = 0; c < C; ++c)
        {
            out(c, r) = in(r, c);
        }
    }
    return out;
}

/*
template<int...>
struct hej
{
    static const size_t value = 2;
};

template<typename T>
sarray<T, typename hej<elements...>::value> make_vector2(int... elements)
{
    return sarray<T, sizeof...(elements)>();
}
*/

} // namespace gal
