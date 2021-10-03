#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_math_special_functions)
    #include <cmath>
namespace mc {
using std::beta;
using std::cyl_bessel_i;
using std::cyl_bessel_j;
using std::cyl_bessel_k;
using std::cyl_neumann;
using std::ellint_1;
using std::ellint_2;
using std::ellint_3;
using std::expint;
using std::hermite;
using std::sph_bessel;
using std::sph_neumann;
} // namespace mc
#else
    #include <boost/math/special_functions.hpp>
namespace mc {
using boost::math::beta;
using boost::math::cyl_bessel_i;
using boost::math::cyl_bessel_j;
using boost::math::cyl_bessel_k;
using boost::math::cyl_neumann;
using boost::math::ellint_1;
using boost::math::ellint_2;
using boost::math::ellint_3;
using boost::math::expint;
using boost::math::hermite;
using boost::math::legendre_p;
using boost::math::sph_bessel;
using boost::math::sph_neumann;
} // namespace mc
#endif
