#pragma once

#include <thrust/functional.h>
#include <newton/detail/scalar_math.hpp>

namespace newton
{
namespace detail
{


template<typename T>
  struct absolute_value
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return abs(x);
  }
}; // end absolute_value


template<typename T>
  struct arc_cosine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return acos(x);
  }
}; // end arc_cosine


template<typename T>
  struct arc_sine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return asin(x);
  }
}; // end arc_sine


template<typename T>
  struct arc_tangent
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return atan(x);
  }
}; // end arc_tangent


template<typename T>
  struct arc_tangent2
    : thrust::binary_function<T,T,T>
{
  inline __host__ __device__
  T operator()(const T &x, const T &y) const
  {
    return atan2(x,y);
  }
}; // end arc_tangent2


template<typename T>
  struct cosine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return cos(x);
  }
}; // end cosine


template<typename T>
  struct error_function
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return erf(x);
  }
}; // end error_function


template<typename T>
  struct exponential
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return exp(x);
  }
}; // end exponential


template<typename T>
  struct hyperbolic_cosine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return cosh(x);
  }
}; // end hyperbolic_cosine


template<typename T>
  struct hyperbolic_sine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return sinh(x);
  }
}; // end hyperbolic_sine


template<typename T>
  struct hyperbolic_tangent
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return tanh(x);
  }
}; // end hyperbolic_tangent


template<typename T>
  struct logarithm
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return log(x);
  }
}; // end logarithm


template<typename T>
  struct logarithm10
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return log10(x);
  }
}; // end logarithm10


template<typename T>
  struct power
    : thrust::binary_function<T,T,T>
{
  inline __host__ __device__
  T operator()(const T &x, const T &y) const
  {
    return pow(x,y);
  }
}; // end power


template<typename T>
  struct sine
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return sin(x);
  }
}; // end sine


template<typename T>
  struct square_root
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return sqrt(x);
  }
}; // end square_root


template<typename T>
  struct tangent
    : thrust::unary_function<T,T>
{
  inline __host__ __device__
  T operator()(const T &x) const
  {
    return tan(x);
  }
}; // end tangent


} // end detail
} // end newton

