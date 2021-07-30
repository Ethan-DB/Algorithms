#pragma once

#include <newton/detail/range/range_traits.hpp>
#include <newton/detail/container_traits.hpp>

namespace thrust
{

// XXX WAR CUDA's warnings about __host__ __device__ functions calling __host__ functions
// with this overload for containers
template<typename Container>
inline __host__ __device__
  typename newton::detail::lazy_enable_if_container<
    Container,
    newton::detail::range_iterator<Container>
  >::type
    begin(Container &c)
{
#if __CUDA_ARCH__
  return typename newton::detail::range_iterator<Container>::type();
#else
  return c.begin();
#endif
}

// XXX WAR CUDA's warnings about __host__ __device__ functions calling __host__ functions
// with this overload for containers
template<typename Container>
inline __host__ __device__
  typename newton::detail::lazy_enable_if_container<
    Container,
    newton::detail::range_iterator<const Container>
  >::type
    begin(const Container &c)
{
#if __CUDA_ARCH__
  return typename newton::detail::range_iterator<const Container>::type();
#else
  return c.begin();
#endif
}

// XXX WAR CUDA's warnings about __host__ __device__ functions calling __host__ functions
// with this overload for containers
template<typename Container>
inline __host__ __device__
  typename newton::detail::lazy_enable_if_container<
    Container,
    newton::detail::range_iterator<Container>
  >::type
    end(Container &c)
{
#if __CUDA_ARCH__
  return typename newton::detail::range_iterator<Container>::type();
#else
  return c.end();
#endif
}

// XXX WAR CUDA's warnings about __host__ __device__ functions calling __host__ functions
// with this overload for containers
template<typename Container>
inline __host__ __device__
  typename newton::detail::lazy_enable_if_container<
    Container,
    newton::detail::range_iterator<const Container>
  >::type
    end(const Container &c)
{
#if __CUDA_ARCH__
  return typename newton::detail::range_iterator<const Container>::type();
#else
  return c.end();
#endif
}


} // end thrust

namespace newton
{
namespace detail
{


template<typename T, std::size_t N>
inline __host__ __device__
  typename range_iterator<T[N]>::type
    begin(T (&array)[N])
{
  return array;
}

template<typename T, std::size_t N>
inline __host__ __device__
  typename range_iterator<T[N]>::type
    end(T (&array)[N])
{
  return array + N;
}


} // end detail
} // end newton

