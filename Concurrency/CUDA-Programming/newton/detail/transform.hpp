#pragma once

#include <newton/detail/range/range_traits.hpp>
#include <newton/detail/range/transform_range.hpp>
#include <newton/detail/zip.hpp>

namespace newton
{
namespace detail
{


template<typename Range, typename AdaptableUnaryFunction>
  class transform1_result
{
  typedef typename range_iterator<Range>::type iterator;

  public:
    typedef transform_range<AdaptableUnaryFunction, iterator> type;
};


template<typename Range, typename AdaptableUnaryFunction>
inline __host__ __device__
typename transform1_result<Range,AdaptableUnaryFunction>::type
transform(Range &rng, AdaptableUnaryFunction f)
{
  return make_transform_range(rng,f);
}


template<typename Range, typename AdaptableUnaryFunction>
inline __host__ __device__
typename transform1_result<const Range,AdaptableUnaryFunction>::type
transform(const Range &rng, AdaptableUnaryFunction f)
{
  return make_transform_range(rng,f);
}


namespace transform_detail
{

template<typename AdaptableBinaryFunction>
  struct unpack_and_apply2
{
  typedef typename AdaptableBinaryFunction::result_type result_type;

  AdaptableBinaryFunction m_f;

  inline __host__ __device__
  unpack_and_apply2(AdaptableBinaryFunction f)
    : m_f(f)
  {}

  template<typename Tuple>
  inline __host__ __device__
  result_type operator()(const Tuple &t) const
  {
    return m_f(thrust::get<0>(t), thrust::get<1>(t));
  }
}; // end unpack_and_apply2

} // end transform_detail


template<typename Range1, typename Range2, typename AdaptableBinaryFunction>
  class transform2_result
{
  typedef typename zip2_result<Range1,Range2>::type                    zipped_range_type;
  typedef transform_detail::unpack_and_apply2<AdaptableBinaryFunction> functor_type;
  
  public:
    typedef typename transform1_result<zipped_range_type, functor_type>::type type;
}; // end transform2_result


template<typename Range1, typename Range2, typename AdaptableBinaryFunction>
inline __host__ __device__
  typename transform2_result<Range1,Range2,AdaptableBinaryFunction>::type
    transform(Range1 &rng1, Range2 &rng2, AdaptableBinaryFunction f)
{
  using namespace transform_detail;
  return transform(zip(rng1, rng2), unpack_and_apply2<AdaptableBinaryFunction>(f));
} // end transform()

template<typename Range1, typename Range2, typename AdaptableBinaryFunction>
inline __host__ __device__
  typename transform2_result<Range1,const Range2,AdaptableBinaryFunction>::type
    transform(Range1 &rng1, const Range2 &rng2, AdaptableBinaryFunction f)
{
  using namespace transform_detail;
  return transform(zip(rng1, rng2), unpack_and_apply2<AdaptableBinaryFunction>(f));
} // end transform()


template<typename Range1, typename Range2, typename AdaptableBinaryFunction>
inline __host__ __device__
  typename transform2_result<const Range1,Range2,AdaptableBinaryFunction>::type
    transform(const Range1 &rng1, Range2 &rng2, AdaptableBinaryFunction f)
{
  using namespace transform_detail;
  return transform(zip(rng1, rng2), unpack_and_apply2<AdaptableBinaryFunction>(f));
} // end transform()


template<typename Range1, typename Range2, typename AdaptableBinaryFunction>
inline __host__ __device__
  typename transform2_result<const Range1,const Range2,AdaptableBinaryFunction>::type
    transform(const Range1 &rng1, const Range2 &rng2, AdaptableBinaryFunction f)
{
  using namespace transform_detail;
  return transform(zip(rng1, rng2), unpack_and_apply2<AdaptableBinaryFunction>(f));
} // end transform()


} // end detail
} // end newton

