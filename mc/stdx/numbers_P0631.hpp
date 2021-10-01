#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_math_constants)
#include <numbers>
namespace mc {
namespace numbers {
    using std::numbers::e;          // NOLINT(readability-identifier-naming)
    using std::numbers::egamma;     // NOLINT(readability-identifier-naming)
    using std::numbers::inv_pi;     // NOLINT(readability-identifier-naming)
    using std::numbers::inv_sqrt3;  // NOLINT(readability-identifier-naming)
    using std::numbers::inv_sqrtpi; // NOLINT(readability-identifier-naming)
    using std::numbers::ln10;       // NOLINT(readability-identifier-naming)
    using std::numbers::ln2;        // NOLINT(readability-identifier-naming)
    using std::numbers::log10e;     // NOLINT(readability-identifier-naming)
    using std::numbers::log2e;      // NOLINT(readability-identifier-naming)
    using std::numbers::phi;        // NOLINT(readability-identifier-naming)
    using std::numbers::pi;         // NOLINT(readability-identifier-naming)
    using std::numbers::sqrt2;      // NOLINT(readability-identifier-naming)
    using std::numbers::sqrt3;      // NOLINT(readability-identifier-naming)
}
}
#else
namespace mc {
namespace numbers {
    // clang-format off
    template <typename T> constexpr auto e_v           = static_cast<T>(2.7182818284590452353602874713526625L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto log2e_v       = static_cast<T>(1.4426950408889634073599246810018921L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto log10e_v      = static_cast<T>(0.4342944819032518276511289189166051L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto pi_v          = static_cast<T>(3.1415926535897932384626433832795028L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto inv_sqrtpi_v  = static_cast<T>(0.564189583547756286948079451560772L);  // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto inv_pi_v      = static_cast<T>(0.3183098861837906715377675267450287L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto ln2_v         = static_cast<T>(0.6931471805599453094172321214581766L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto ln10_v        = static_cast<T>(2.3025850929940456840179914546843642L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto sqrt2_v       = static_cast<T>(1.4142135623730950488016887242096981L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto sqrt3_v       = static_cast<T>(1.7320508075688772935274463415058724L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto inv_sqrt3_v   = static_cast<T>(0.5773502691896257645091487805019574L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto egamma_v      = static_cast<T>(0.5772156649015328606065120900824024L); // NOLINT(readability-identifier-naming)
    template <typename T> constexpr auto phi_v         = static_cast<T>(1.6180339887498948482045868343656381L); // NOLINT(readability-identifier-naming)

    constexpr double e          = e_v<double>;           // NOLINT(readability-identifier-naming)
    constexpr double log2e      = log2e_v<double>;       // NOLINT(readability-identifier-naming)
    constexpr double log10e     = log10e_v<double>;      // NOLINT(readability-identifier-naming)
    constexpr double pi         = pi_v<double>;          // NOLINT(readability-identifier-naming)
    constexpr double inv_pi     = inv_pi_v<double>;      // NOLINT(readability-identifier-naming)
    constexpr double inv_sqrtpi = inv_sqrtpi_v<double>;  // NOLINT(readability-identifier-naming)
    constexpr double ln2        = ln2_v<double>;         // NOLINT(readability-identifier-naming)
    constexpr double ln10       = ln10_v<double>;        // NOLINT(readability-identifier-naming)
    constexpr double sqrt2      = sqrt2_v<double>;       // NOLINT(readability-identifier-naming)
    constexpr double sqrt3      = sqrt3_v<double>;       // NOLINT(readability-identifier-naming)
    constexpr double inv_sqrt3  = inv_sqrt3_v<double>;   // NOLINT(readability-identifier-naming)
    constexpr double egamma     = egamma_v<double>;      // NOLINT(readability-identifier-naming)
    constexpr double phi        = phi_v<double>;         // NOLINT(readability-identifier-naming)
    // clang-format on
} // namespace numbers
} // namespace mc
#endif
