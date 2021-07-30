#pragma once

#include <thrust/iterator/zip_iterator.h>
#include <newton/detail/range/range.hpp>

namespace newton
{
namespace detail
{

template<typename IteratorTuple>
  class zip_range
    : public newton::detail::range<
        thrust::zip_iterator<IteratorTuple>
      >
{
  private:
    typedef newton::detail::range<
      thrust::zip_iterator<IteratorTuple>
    > super_t;

  public:
    inline __host__ __device__
    zip_range(IteratorTuple first, IteratorTuple last)
      : super_t(first,last)
    {}
}; // end zip_range

template<typename Range1, typename Range2>
inline __host__ __device__
zip_range<
  thrust::tuple<
    typename range_iterator<Range1>::type,
    typename range_iterator<Range2>::type
  >
>
make_zip_range(Range1 &rng1, Range2 &rng2)
{
  typedef thrust::tuple<
    typename range_iterator<Range1>::type,
    typename range_iterator<Range2>::type
  > iterator_tuple;

  return zip_range<iterator_tuple>(thrust::make_tuple(begin(rng1), begin(rng2)),
                                   thrust::make_tuple(end(rng1), end(rng2)));
}

template<typename Range1, typename Range2>
inline __host__ __device__
zip_range<
  thrust::tuple<
    typename range_iterator<Range1>::type,
    typename range_iterator<const Range2>::type
  >
>
make_zip_range(Range1 &rng1, const Range2 &rng2)
{
  typedef thrust::tuple<
    typename range_iterator<Range1>::type,
    typename range_iterator<const Range2>::type
  > iterator_tuple;

  return zip_range<iterator_tuple>(thrust::make_tuple(begin(rng1), begin(rng2)),
                                   thrust::make_tuple(end(rng1), end(rng2)));
}

template<typename Range1, typename Range2>
inline __host__ __device__
zip_range<
  thrust::tuple<
    typename range_iterator<const Range1>::type,
    typename range_iterator<Range2>::type
  >
>
make_zip_range(const Range1 &rng1, Range2 &rng2)
{
  typedef thrust::tuple<
    typename range_iterator<const Range1>::type,
    typename range_iterator<Range2>::type
  > iterator_tuple;

  return zip_range<iterator_tuple>(thrust::make_tuple(begin(rng1), begin(rng2)),
                                   thrust::make_tuple(end(rng1), end(rng2)));
}

template<typename Range1, typename Range2>
inline __host__ __device__
zip_range<
  thrust::tuple<
    typename range_iterator<const Range1>::type,
    typename range_iterator<const Range2>::type
  >
>
make_zip_range(const Range1 &rng1, const Range2 &rng2)
{
  typedef thrust::tuple<
    typename range_iterator<const Range1>::type,
    typename range_iterator<const Range2>::type
  > iterator_tuple;

  return zip_range<iterator_tuple>(thrust::make_tuple(begin(rng1), begin(rng2)),
                                   thrust::make_tuple(end(rng1), end(rng2)));
}

} // end detail
} // end newton

