#pragma once

namespace newton
{
namespace detail
{

template<typename _Tp, _Tp __v>
  struct integral_constant
{
  static const _Tp                      value = __v;
  typedef _Tp                           value_type;
  typedef integral_constant<_Tp, __v>   type;
};

typedef integral_constant<bool, true>     true_type;
typedef integral_constant<bool, false>    false_type;

template<bool, typename T = void> struct enable_if {};
template<typename T>              struct enable_if<true, T> {typedef T type;};
template<bool, typename T> struct lazy_enable_if {};
template<typename T>       struct lazy_enable_if<true, T> {typedef typename T::type type;};

template<bool condition, typename T = void> struct disable_if : enable_if<!condition, T> {};
template<bool condition, typename T>        struct lazy_disable_if : lazy_enable_if<!condition, T> {};


} // end detail
} // end newton

