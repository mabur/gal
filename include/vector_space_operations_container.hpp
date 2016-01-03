#pragma once

////////////////////////////////////////////////////////////////////////////////
// add

template<typename ContainerIn1, typename ContainerIn2, typename ContainerOut,
	typename check_sum<value_type<ContainerIn1>, value_type<ContainerIn2>, value_type<ContainerOut>> = 0>
void add(const ContainerIn1& left, const ContainerIn2& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	add(begin(left), end(left), begin(right), begin(out));
}

template<typename ElementIn, typename ContainerIn, typename ContainerOut,
	typename check_sum<ElementIn, value_type<ContainerIn>, value_type<ContainerOut>> = 0>
void add(const ElementIn& left, const ContainerIn& right, ContainerOut& out)
{
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	add(left, begin(right), end(right), begin(out));
}

template<typename ContainerIn, typename ElementIn, typename ContainerOut,
	typename check_sum<value_type<ContainerIn>, ElementIn, value_type<ContainerOut>> = 0>
void add(const ContainerIn& left, const ElementIn& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	using std::begin;
	using std::end;
	add(begin(left), end(left), right, begin(out));
}

////////////////////////////////////////////////////////////////////////////////
// subtract

template<typename ContainerIn1, typename ContainerIn2, typename ContainerOut,
	typename check_difference<value_type<ContainerIn1>, value_type<ContainerIn2>, value_type<ContainerOut>> = 0>
void subtract(const ContainerIn1& left, const ContainerIn2& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	subtract(begin(left), end(left), begin(right), begin(out));
}

template<typename ElementIn, typename ContainerIn, typename ContainerOut,
	typename check_difference<ElementIn, value_type<ContainerIn>, value_type<ContainerOut>> = 0>
void subtract(const ElementIn& left, const ContainerIn& right, ContainerOut& out)
{
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	subtract(left, begin(right), end(right), begin(out));
}

template<typename ContainerIn, typename ElementIn, typename ContainerOut,
	typename check_difference<value_type<ContainerIn>, ElementIn, value_type<ContainerOut>> = 0>
void subtract(const ContainerIn& left, const ElementIn& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	using std::begin;
	using std::end;
	subtract(begin(left), end(left), right, begin(out));
}

////////////////////////////////////////////////////////////////////////////////
// multiply

template<typename ContainerIn1, typename ContainerIn2, typename ContainerOut,
	typename check_product<value_type<ContainerIn1>, value_type<ContainerIn2>, value_type<ContainerOut>> = 0>
void multiply(const ContainerIn1& left, const ContainerIn2& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	multiply(begin(left), end(left), begin(right), begin(out));
}

template<typename ElementIn, typename ContainerIn, typename ContainerOut,
	typename check_product<ElementIn, value_type<ContainerIn>, value_type<ContainerOut>> = 0>
void multiply(const ElementIn& left, const ContainerIn& right, ContainerOut& out)
{
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	multiply(left, begin(right), end(right), begin(out));
}

template<typename ContainerIn, typename ElementIn, typename ContainerOut,
	typename check_product<value_type<ContainerIn>, ElementIn, value_type<ContainerOut>> = 0>
void multiply(const ContainerIn& left, const ElementIn& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	using std::begin;
	using std::end;
	multiply(begin(left), end(left), right, begin(out));
}

////////////////////////////////////////////////////////////////////////////////
// divide

template<typename ContainerIn1, typename ContainerIn2, typename ContainerOut,
	typename check_ratio<value_type<ContainerIn1>, value_type<ContainerIn2>, value_type<ContainerOut>> = 0>
void divide(const ContainerIn1& left, const ContainerIn2& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	multiply(begin(left), end(left), begin(right), begin(out));
}

template<typename ElementIn, typename ContainerIn, typename ContainerOut,
	typename check_ratio<ElementIn, value_type<ContainerIn>, value_type<ContainerOut>> = 0>
void divide(const ElementIn& left, const ContainerIn& right, ContainerOut& out)
{
	assert(right.size() == out.size());
	using std::begin;
	using std::end;
	multiply(left, begin(right), end(right), begin(out));
}

template<typename ContainerIn, typename ElementIn, typename ContainerOut,
	typename check_ratio<value_type<ContainerIn>, ElementIn, value_type<ContainerOut>> = 0>
void divide(const ContainerIn& left, const ElementIn& right, ContainerOut& out)
{
	assert(left.size() == out.size());
	using std::begin;
	using std::end;
	multiply(begin(left), end(left), right, begin(out));
}
