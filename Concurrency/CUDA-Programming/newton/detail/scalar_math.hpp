#pragma once

// overloads for non-double primitives for the
// functions used in functors within newton/functional.hpp

#include <cmath>
#include <math.h>

namespace newton
{
namespace detail
{


inline __host__ __device__
float abs(float x)
{
  return ::fabs(x);
} // end abs


template<typename T>
inline __host__ __device__
T abs(T x)
{
  return x < 0 ? -x : x;
} // end abs()


inline __host__ __device__
float acos(float x)
{
  return acosf(x);
} // acos()


inline __host__ __device__
float asin(float x)
{
  return asinf(x);
} // asin()


inline __host__ __device__
float atan(float x)
{
  return atanf(x);
} // atan()


inline __host__ __device__
float atan2(float x, float y)
{
  return atan2f(x,y);
} // atan2()


inline __host__ __device__
float cos(float x)
{
  return cosf(x);
} // cos()


inline __host__ __device__
float erf(float x)
{
  return erff(x);
} // end erf()

inline __host__ __device__
float exp(float x)
{
  return expf(x);
} // exp()


inline __host__ __device__
float cosh(float x)
{
  return coshf(x);
} // cosh()


inline __host__ __device__
float sinh(float x)
{
  return sinhf(x);
} // sinh()


inline __host__ __device__
float tanh(float x)
{
  return tanhf(x);
} // tanh()


inline __host__ __device__
float log(float x)
{
  return logf(x);
} // log()


inline __host__ __device__
float log10(float x)
{
  return log10f(x);
} // log10()


template<typename T>
inline __host__ __device__
T mod(T numerator, T denominator)
{
  return numerator % denominator;
} // end mod()


inline __host__ __device__
double mod(double numerator, double denominator)
{
  return fmod(numerator,denominator);
} // end mod()


inline __host__ __device__
float mod(float numerator, float denominator)
{
  return fmod(numerator,denominator);
} // end mod()


inline __host__ __device__
float pow(float x, float y)
{
  return powf(x,y);
} // pow()


inline __host__ __device__
float sin(float x)
{
  return sinf(x);
} // sin()


inline __host__ __device__
float sqrt(float x)
{
  return sqrtf(x);
} // sqrt()


inline __host__ __device__
float tan(float x)
{
  return tanf(x);
} // tan()


} // end detail
} // end newton

