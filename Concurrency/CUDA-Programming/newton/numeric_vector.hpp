#pragma once

#include <thrust/detail/vector_base.h>
#include <thrust/device_malloc_allocator.h>
#include <newton/detail/arithmetic.hpp>
#include <newton/detail/type_traits.hpp>
#include <vector>


namespace newton
{


// XXX for now, use malloc_allocator, but we'll probably
//     want to use a better default, e.g. an allocator
//     that does not initialize elements
//     see http://stackoverflow.com/questions/7218574/avoiding-default-construction-of-elements-in-standard-containers
template<typename T, typename Allocator = thrust::device_malloc_allocator<T> >
  class numeric_vector
    : public thrust::detail::vector_base<T,Allocator>
{
  private:
    typedef thrust::detail::vector_base<T,Allocator> super_t;

  public:
    typedef typename super_t::size_type  size_type;
    typedef typename super_t::value_type value_type;

    inline numeric_vector()
      : super_t()
    {}

    inline explicit numeric_vector(size_type n, const value_type &value = value_type())
      : super_t(n,value)
    {}

    inline numeric_vector(const numeric_vector &x)
      : super_t(x)
    {}

    template<typename Range>
    inline numeric_vector(const Range &rng, typename detail::enable_if_range<Range>::type * = 0)
      : super_t(newton::detail::adl_begin(rng), newton::detail::adl_end(rng))
    {}

    template<typename InputIterator>
    inline numeric_vector(InputIterator first, InputIterator last)
      : super_t(first,last)
    {}

    inline numeric_vector &operator=(const numeric_vector &x)
    {
      super_t::operator=(x);
      return *this;
    }

    template<typename Range>
    typename detail::enable_if_range<
      Range,
      numeric_vector &
    >::type
    operator=(const Range &rng)
    {
      this->assign(rng.begin(),rng.end());
      return *this;
    }
}; // end numeric_vector

template<typename T, typename Allocator>
__host__ __device__
inline typename numeric_vector<T,Allocator>::iterator
  begin(numeric_vector<T,Allocator> &rng)
{
#if __CUDA_ARCH__
  return typename numeric_vector<T,Allocator>::iterator();
#else
  return rng.begin();
#endif
}

template<typename T, typename Allocator>
__host__ __device__
inline typename numeric_vector<T,Allocator>::const_iterator
  begin(const numeric_vector<T,Allocator> &rng)
{
#if __CUDA_ARCH__
  return typename numeric_vector<T,Allocator>::const_iterator();
#else
  return rng.begin();
#endif
}

template<typename T, typename Allocator>
__host__ __device__
inline typename numeric_vector<T,Allocator>::iterator
  end(numeric_vector<T,Allocator> &rng)
{
#if __CUDA_ARCH__
  return typename numeric_vector<T,Allocator>::iterator();
#else
  return rng.end();
#endif
}

template<typename T, typename Allocator>
__host__ __device__
inline typename numeric_vector<T,Allocator>::const_iterator
  end(const numeric_vector<T,Allocator> &rng)
{
#if __CUDA_ARCH__
  return typename numeric_vector<T,Allocator>::const_iterator();
#else
  return rng.end();
#endif
}


} // end newton

