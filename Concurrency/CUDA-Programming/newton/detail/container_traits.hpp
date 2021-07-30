#pragma once

#include <thrust/detail/type_traits.h>
#include <newton/detail/type_traits.hpp>

namespace newton
{
namespace detail
{
namespace container_traits_detail
{


template<typename T>
  struct has_allocator_type
{
  typedef char yes_type;
  typedef int  no_type;
  template<typename S> static yes_type test(typename S::allocator_type *);
  template<typename S> static no_type  test(...);
  static bool const value = sizeof(test<T>(0)) == sizeof(yes_type);
  typedef thrust::detail::integral_constant<bool, value> type;
}; // end has_allocator_type

  
} // end container_traits_detail


template<typename T>
  struct is_container
    : container_traits_detail::has_allocator_type<T>
{};


template<typename T, typename Result = void>
  struct enable_if_container
    : detail::enable_if<
        is_container<T>::value,
        Result
      >
{};


template<typename T, typename Result>
  struct lazy_enable_if_container
    : detail::lazy_enable_if<
        is_container<T>::value,
        Result
      >
{};


template<typename T, typename Result = void>
  struct disable_if_container
    : detail::disable_if<
        is_container<T>::value,
        Result
      >
{};


template<typename T, typename Result>
  struct lazy_disable_if_container
    : detail::lazy_disable_if<
        is_container<T>::value,
        Result
      >
{};


} // end detail
} // end newton

