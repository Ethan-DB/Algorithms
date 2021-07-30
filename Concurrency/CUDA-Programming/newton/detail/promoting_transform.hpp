#pragma once

#include <thrust/detail/type_traits.h>
#include <thrust/detail/minmax.h>
#include <newton/detail/type_traits.hpp>
#include <newton/detail/range/range_traits.hpp>
#include <newton/detail/range/range.hpp>
#include <newton/detail/range/constant_range.hpp>
#include <newton/detail/transform.hpp>

namespace newton
{
namespace detail
{
namespace promoting_transform_detail
{


template<typename Range1, typename Range2>
  struct min_size_result
    : thrust::detail::eval_if<
        is_range<Range1>::value,
        range_difference<Range1>,
        range_difference<Range2>
      >
{};


template<typename Range1, typename Range2>
inline __host__ __device__
typename lazy_enable_if_ranges<
  Range1, Range2,
  range_difference<Range1>
>::type
  min_size(const Range1 &rng1, const Range2 &rng2)
{
  typedef typename range_difference<Range1>::type result_type;
  return thrust::min<result_type>(size(rng1), size(rng2));
} // end min_size()


template<typename Range, typename Scalar>
inline __host__ __device__
typename lazy_enable_if_range_and_scalar<
  Range, Scalar,
  range_difference<Range>
>::type
  min_size(const Range &rng, const Scalar &)
{
  return size(rng);
} // end min_size()


template<typename Scalar, typename Range>
inline __host__ __device__
typename lazy_enable_if_scalar_and_range<
  Scalar, Range,
  range_difference<Range>
>::type
  min_size(const Scalar &, const Range &rng)
{
  return size(rng);
} // end min_size()


template<typename Range>
  struct take_result
{
  typedef range<typename range_iterator<Range>::type> type;
};


template<typename RangeOrScalar, typename Size>
  struct rangify_result
    : thrust::detail::eval_if<
        is_range<RangeOrScalar>::value,
        take_result<RangeOrScalar>,
        thrust::detail::identity_<
          constant_range<
            typename thrust::detail::remove_const<RangeOrScalar>::type
          >
        >
      >
{};


template<typename Range, typename Size>
inline __host__ __device__
typename lazy_enable_if_range<
  Range,
  rangify_result<Range,Size>
>::type
  rangify(Range &x, Size n)
{
  return take(x, n);
}


template<typename Range, typename Size>
inline __host__ __device__
typename lazy_enable_if_range<
  Range,
  rangify_result<const Range,Size>
>::type
  rangify(const Range &x, Size n)
{
  return take(x, n);
}


template<typename Scalar, typename Size>
inline __host__ __device__
typename lazy_disable_if_range<
  Scalar,
  rangify_result<Scalar,Size>
>::type
  rangify(Scalar x, Size n)
{
  return make_constant_range(x, n);
}


} // end promoting_transform_detail


template<typename RangeOrScalar1, typename RangeOrScalar2, typename AdaptableBinaryFunction>
  class promoting_transform_result
{
  typedef typename promoting_transform_detail::min_size_result<
    RangeOrScalar1,
    RangeOrScalar2
  >::type size_type;

  typedef typename promoting_transform_detail::rangify_result<
    RangeOrScalar1,
    size_type
  >::type rangify_type1;

  typedef typename promoting_transform_detail::rangify_result<
    RangeOrScalar2,
    size_type
  >::type rangify_type2;

  public:
    typedef typename transform2_result<const rangify_type1, const rangify_type2, AdaptableBinaryFunction>::type type;
};


// promoting_transform expects at least one of its arguments to be a range
// if the other isn't a range, it is promoted to a constant_range
template<typename RangeOrScalar1, typename RangeOrScalar2, typename AdaptableBinaryFunction>
inline __host__ __device__
typename promoting_transform_result<
  RangeOrScalar1, RangeOrScalar2, AdaptableBinaryFunction
>::type
  promoting_transform(RangeOrScalar1 &x, RangeOrScalar2 &y, AdaptableBinaryFunction f)
{
  using namespace promoting_transform_detail;
  typename min_size_result<RangeOrScalar1,RangeOrScalar2>::type n = min_size(x,y);
  return transform(rangify(x,n), rangify(y,n), f);
}

template<typename RangeOrScalar1, typename RangeOrScalar2, typename AdaptableBinaryFunction>
inline __host__ __device__
typename promoting_transform_result<
  RangeOrScalar1, const RangeOrScalar2, AdaptableBinaryFunction
>::type
  promoting_transform(RangeOrScalar1 &x, const RangeOrScalar2 &y, AdaptableBinaryFunction f)
{
  using namespace promoting_transform_detail;
  typename min_size_result<RangeOrScalar1,RangeOrScalar2>::type n = min_size(x,y);
  return transform(rangify(x,n), rangify(y,n), f);
}

template<typename RangeOrScalar1, typename RangeOrScalar2, typename AdaptableBinaryFunction>
inline __host__ __device__
typename promoting_transform_result<
  const RangeOrScalar1, RangeOrScalar2, AdaptableBinaryFunction
>::type
  promoting_transform(const RangeOrScalar1 &x, RangeOrScalar2 &y, AdaptableBinaryFunction f)
{
  using namespace promoting_transform_detail;
  typename min_size_result<RangeOrScalar1,RangeOrScalar2>::type n = min_size(x,y);
  return transform(rangify(x,n), rangify(y,n), f);
}

template<typename RangeOrScalar1, typename RangeOrScalar2, typename AdaptableBinaryFunction>
inline __host__ __device__
typename promoting_transform_result<
  const RangeOrScalar1, const RangeOrScalar2, AdaptableBinaryFunction
>::type
  promoting_transform(const RangeOrScalar1 &x, const RangeOrScalar2 &y, AdaptableBinaryFunction f)
{
  using namespace promoting_transform_detail;
  typename min_size_result<RangeOrScalar1,RangeOrScalar2>::type n = min_size(x,y);
  return transform(rangify(x,n), rangify(y,n), f);
}


} // end detail
} // end newton

