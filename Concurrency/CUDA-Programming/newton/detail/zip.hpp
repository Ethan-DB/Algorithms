#pragma once

#include <newton/detail/range/zip_range.hpp>
#include <thrust/tuple.h>
#include <thrust/iterator/zip_iterator.h>

namespace newton
{
namespace detail
{


template<typename Range>
  struct zip1_result
{
  typedef zip_range<thrust::tuple<typename range_iterator<Range>::type> > type;
};


template<typename Range>
inline __host__ __device__
  typename zip1_result<Range>::type
    zip(Range &rng)
{
  typedef typename zip1_result<Range>::type result_type;
  return result_type(thrust::make_tuple(rng));
}

template<typename Range>
inline __host__ __device__
  typename zip1_result<const Range>::type
    zip(const Range &rng)
{
  typedef typename zip1_result<const Range>::type result_type;
  return result_type(thrust::make_tuple(rng));
}


template<typename Range1, typename Range2>
  struct zip2_result
{
  typedef zip_range<
    thrust::tuple<
      typename range_iterator<Range1>::type,
      typename range_iterator<Range2>::type
    >
  > type;
};


template<typename Range1, typename Range2>
inline __host__ __device__
  typename zip2_result<Range1,Range2>::type
    zip(Range1 &rng1, Range2 &rng2)
{
  return make_zip_range(rng1,rng2);
}

template<typename Range1, typename Range2>
inline __host__ __device__
  typename zip2_result<Range1,const Range2>::type
    zip(Range1 &rng1, const Range2 &rng2)
{
  return make_zip_range(rng1,rng2);
}

template<typename Range1, typename Range2>
inline __host__ __device__
  typename zip2_result<const Range1,Range2>::type
    zip(const Range1 &rng1, Range2 &rng2)
{
  return make_zip_range(rng1,rng2);
}

template<typename Range1, typename Range2>
inline __host__ __device__
  typename zip2_result<const Range1,const Range2>::type
    zip(const Range1 &rng1, const Range2 &rng2)
{
  return make_zip_range(rng1,rng2);
}


} // end detail
} // end newton

