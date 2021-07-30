#pragma once

#include <thrust/detail/type_traits.h>
#include <newton/detail/range/range_traits.hpp>
#include <newton/detail/transform.hpp>
#include <newton/detail/promoting_transform.hpp>

namespace newton
{
namespace detail
{


template<typename RangeOrScalar>
  struct range_value_or_identity
    : thrust::detail::eval_if<
        is_range<RangeOrScalar>::value,
        range_value<RangeOrScalar>,
        thrust::detail::identity_<RangeOrScalar>
      >
{};


} // end detail
} // end newton


#if __cplusplus < 201103L


#define __NEWTON_DEFINE_UNARY_RANGE_FUNCTION(function_name, scalar_functor) \
template<typename Range> \
inline __host__ __device__ \
  typename detail::lazy_enable_if_range< \
    Range, \
    detail::transform1_result< \
      const Range, \
      scalar_functor<typename detail::range_value<Range>::type> \
    > \
  >::type \
    function_name(const Range &rng) \
{ \
  return detail::transform(rng, scalar_functor<typename detail::range_value<Range>::type>()); \
}


#define __NEWTON_DEFINE_BINARY_RANGE_FUNCTION(function_name, scalar_functor) \
template<typename RangeOrScalar1, typename RangeOrScalar2> \
inline __host__ __device__ \
  typename detail::lazy_enable_if_at_least_one_is_range< \
    RangeOrScalar1, RangeOrScalar2, \
    detail::promoting_transform_result< \
      const RangeOrScalar1, \
      const RangeOrScalar2, \
      scalar_functor<typename detail::range_value_or_identity<RangeOrScalar1>::type> \
    > \
  >::type \
    function_name(const RangeOrScalar1 &lhs, const RangeOrScalar2 &rhs) \
{ \
  return detail::promoting_transform(lhs, rhs, scalar_functor<typename detail::range_value_or_identity<RangeOrScalar1>::type>()); \
}

#else


#define __NEWTON_DEFINE_UNARY_RANGE_FUNCTION(function_name, scalar_functor) \
template<typename Range, \
         typename = typename detail::enable_if_range<Range>::type \
        > \
inline __host__ __device__ \
auto function_name(const Range &rng) \
  -> decltype(detail::transform(rng, scalar_functor<typename detail::range_value<Range>::type>())) \
{ \
  return detail::transform(rng, scalar_functor<typename detail::range_value<Range>::type>()); \
}


#define __NEWTON_DEFINE_BINARY_RANGE_FUNCTION(function_name, scalar_functor) \
template<typename RangeOrScalar1, typename RangeOrScalar2, \
         typename = typename detail::lazy_enable_if_at_least_one_is_range< \
           RangeOrScalar1, RangeOrScalar2 \
         >::type> \
inline __host__ __device__ \
auto function_name(const RangeOrScalar1 &lhs, const RangeOrScalar2 &rhs) \
  -> decltype(detail::promoting_transform(lhs, rhs, scalar_functor<typename detail::range_value_or_identity<RangeOrScalar1>::type>())) \
{ \
  return detail::promoting_transform(lhs, rhs, scalar_functor<typename detail::range_value_or_identity<RangeOrScalar1>::type>()); \
}


#endif // C++11
 
