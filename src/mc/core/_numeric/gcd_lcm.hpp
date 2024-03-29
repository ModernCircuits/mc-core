// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_gcd_lcm)
#include <numeric>

namespace mc {
using std::gcd;
using std::lcm;
}  // namespace mc
#else
#include <type_traits>

namespace mc {
template<typename M, typename N>
[[nodiscard]] constexpr auto gcd(M m, N n) noexcept -> std::common_type_t<M, N>
{
    if (n == 0) { return m; }
    return gcd<M, N>(n, m % n);
}

template<typename M, typename N>
[[nodiscard]] constexpr auto lcm(M m, N n) -> std::enable_if_t<
    std::is_integral_v<M>             //
        && !std::is_same_v<M, bool>   //
        && std::is_integral_v<N>      //
        && !std::is_same_v<N, bool>,  //
    std::common_type_t<M, N>          //
    >
{
    using Common = std::common_type_t<M, N>;
    if ((m == M{}) || (n == N{})) { return 0; }
    return static_cast<Common>(static_cast<Common>(m * n) / gcd(m, n));
}

}  // namespace mc
#endif
