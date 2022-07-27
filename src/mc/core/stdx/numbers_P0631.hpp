// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_math_constants)
#include <numbers>

namespace mc {
namespace numbers {
using std::numbers::e;
using std::numbers::egamma;
using std::numbers::inv_pi;
using std::numbers::inv_sqrt3;
using std::numbers::inv_sqrtpi;
using std::numbers::ln10;
using std::numbers::ln2;
using std::numbers::log10e;
using std::numbers::log2e;
using std::numbers::phi;
using std::numbers::pi;
using std::numbers::sqrt2;
using std::numbers::sqrt3;
}  // namespace numbers
}  // namespace mc
#else
#include <boost/math/constants/constants.hpp>

namespace mc {
namespace numbers {
// clang-format off
    MC_INLINE_VAR constexpr double e           = boost::math::constants::e<double>();               // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double log2e       = boost::math::constants::log2_e<double>();          // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double log10e      = boost::math::constants::log10_e<double>();         // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double pi          = boost::math::constants::pi<double>();              // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double inv_sqrtpi  = boost::math::constants::one_div_root_pi<double>(); // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double inv_pi      = boost::math::constants::one_div_pi<double>();      // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double ln2         = boost::math::constants::ln_two<double>();          // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double ln10        = boost::math::constants::ln_ten<double>();          // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double sqrt2       = boost::math::constants::root_two<double>();        // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double sqrt3       = boost::math::constants::root_three<double>();      // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double egamma      = boost::math::constants::euler<double>();           // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double phi         = boost::math::constants::phi<double>();             // NOLINT(readability-identifier-naming)
    MC_INLINE_VAR constexpr double inv_sqrt3   = 1.0/boost::math::constants::root_three<double>();  // NOLINT(readability-identifier-naming)
// clang-format on
}  // namespace numbers
}  // namespace mc
#endif
