#pragma once

#include <newton/detail/range/range.hpp>
#include <newton/detail/range/range_traits.hpp>
#include <newton/detail/arithmetic.hpp>
#include <newton/detail/range/constant_range.hpp>

namespace newton
{


// XXX assumes is_arithmetic<typename value_type<Iterator>::type>
template<typename Iterator>
  class numeric_range
    : public newton::detail::range<Iterator>
{
  private:
    typedef newton::detail::range<Iterator> super_t;

  public:
    typedef typename super_t::iterator iterator;

    inline __host__ __device__
    numeric_range(iterator first, iterator last)
      : super_t(first,last)
    {}

    template<typename Range>
    inline __host__ __device__
    numeric_range(Range &rng)
      : super_t(rng)
    {}

    template<typename Range>
    inline __host__ __device__
    numeric_range(const Range &rng)
      : super_t(rng)
    {}
};

template<typename Iterator>
inline __host__ __device__
  typename numeric_range<Iterator>::iterator
    begin(const numeric_range<Iterator> &rng)
{
  return rng.begin();
}

template<typename Iterator>
inline __host__ __device__
  typename numeric_range<Iterator>::iterator
    end(const numeric_range<Iterator> &rng)
{
  return rng.end();
}

template<typename Iterator>
inline __host__ __device__
  numeric_range<Iterator>
    make_numeric_range(Iterator first, Iterator last)
{
  return numeric_range<Iterator>(first,last);
}

template<typename Range>
inline __host__ __device__
  numeric_range<typename detail::range_iterator<Range> >
    make_numeric_range(Range &rng)
{
  return numeric_range<typename detail::range_iterator<Range> >(rng);
}

template<typename Range>
inline __host__ __device__
  numeric_range<typename detail::range_iterator<const Range> >
    make_numeric_range(const Range &rng)
{
  return numeric_range<typename detail::range_iterator<const Range> >(rng);
}


} // end newton

