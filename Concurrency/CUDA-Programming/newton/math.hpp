#pragma once

#include <newton/detail/define_range_function.hpp>
#include <newton/detail/functional.hpp>

namespace newton
{


__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(abs, detail::absolute_value);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(acos, detail::arc_cosine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(asin, detail::arc_sine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(atan, detail::arc_tangent);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(atan2, detail::arc_tangent2);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(cos, detail::cosine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(cosh, detail::hyperbolic_cosine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(erf, detail::error_function);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(exp, detail::exponential);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(log, detail::logarithm);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(log10, detail::logarithm10);
__NEWTON_DEFINE_BINARY_RANGE_FUNCTION(pow, detail::power);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(sin, detail::sine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(sinh, detail::hyperbolic_sine);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(sqrt, detail::square_root);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(tan, detail::tangent);
__NEWTON_DEFINE_UNARY_RANGE_FUNCTION(tanh, detail::hyperbolic_tangent);


// mirror these functions in namespace detail so that they are
// available to intermediate range expressions such as
// detail::transform_range and detail::constant_range
namespace detail
{


using newton::abs;
using newton::acos;
using newton::asin;
using newton::atan;
using newton::atan2;
using newton::cos;
using newton::cosh;
using newton::erf;
using newton::exp;
using newton::log;
using newton::log10;
using newton::pow;
using newton::sin;
using newton::sinh;
using newton::sqrt;
using newton::tan;
using newton::tanh;


} // end detail
} // end newton

