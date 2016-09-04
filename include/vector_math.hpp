#pragma once
/*
#include <numeric>

#include "arithmetic.hpp"

// Make it optional for the user to choose what header to include:
// * standard like this header
// * another one with expression templates

// optional expression templates
template<typename LeftVector, typename RightVector>
LeftVector& operator+=(LeftVector& a, const RightVector& b)
{
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        a[i] += b[i];
    }
    return a;
}

template<typename LeftVector, typename RightVector>
LeftVector& operator-=(LeftVector& a, const RightVector& b)
{
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        a[i] -= b[i];
    }
    return a;
}

template<typename Vector>
Vector& operator*=(Vector& a, typename const Vector::value_type& b)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        a[i] *= b;
    }
    return a;
}

template<typename Vector>
Vector& operator/=(Vector& a, typename const Vector::value_type& b)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        a[i] /= b;
    }
    return a;
}

template<typename Vector>
Vector operator+(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    auto result = a;
    result += b;
    return result;
}

template<typename Vector>
Vector operator-(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    auto result = a;
    result -= b;
    return result;
}

template<typename Vector>
Vector operator*(const Vector& a, typename const Vector::value_type& b)
{
    auto result = a;
    result *= b;
    return result;
}

template<typename Vector>
Vector operator*(typename const Vector::value_type& a, const Vector& b)
{
    return b * a;
}

template<typename Vector>
Vector operator/(const Vector& a, typename const Vector::value_type& b)
{
    auto result = a;
    result /= b;
    return result;
}
*/