#pragma once

#include <newton/detail/define_range_function.hpp>
#include <newton/detail/scalar_math.hpp>
#include <thrust/functional.h>

namespace newton
{
namespace detail
{


// introduce this version of modulus which calls mod instead of operator%
// mod is itself implemented with operator% for integral types
template<typename T>
  struct modulus
    : thrust::binary_function<T,T,T>
{
  inline __host__ __device__
  T operator()(const T &lhs, const T &rhs) const
  {
    return mod(lhs,rhs);
  }
};


} // end detail


// unary arithmetic
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(operator+, thrust::identity);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(operator-, thrust::negate);

// binary arithmetic
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator/, thrust::divides);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator-, thrust::minus);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator%, detail::modulus);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator*, thrust::multiplies);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator+, thrust::plus);

// binary relational
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator==, thrust::equal_to);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator>,  thrust::greater);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator>=, thrust::greater_equal);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator<,  thrust::less);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator<=, thrust::less_equal);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator!=, thrust::not_equal_to);

// unary logical
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(operator~, thrust::logical_not);

// binary logical
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator&&, thrust::logical_and);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator||, thrust::logical_or);

// binary bitwise
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator&,  thrust::bit_and);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator|,  thrust::bit_or);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(operator^,  thrust::bit_xor);


// put these in namespace ops so that the user can easily make
// arithmetic available to all ranges with a single using directive
namespace ops
{


// arithmetic
using newton::operator/;
using newton::operator-;
using newton::operator%;
using newton::operator*;
using newton::operator+;

// relational
using newton::operator==;
using newton::operator>;
using newton::operator>=;
using newton::operator<;
using newton::operator<=;
using newton::operator!=;

// logical
using newton::operator~;
using newton::operator&&;
using newton::operator||;

// bitwise
using newton::operator&;
using newton::operator|;
using newton::operator^;


} // end namespace ops


// put these in namespace detail so that arithmetic is
// available to detail::transform_range and detail::constant_range
namespace detail
{


// arithmetic
using newton::operator/;
using newton::operator-;
using newton::operator%;
using newton::operator*;
using newton::operator+;

// relational
using newton::operator==;
using newton::operator>;
using newton::operator>=;
using newton::operator<;
using newton::operator<=;
using newton::operator!=;

// logical
using newton::operator~;
using newton::operator&&;
using newton::operator||;

// bitwise
using newton::operator&;
using newton::operator|;
using newton::operator^;


} // end namespace detail
} // end namespace newton

