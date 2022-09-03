// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <cmath>
#include <gcem.hpp>

namespace mc {
MC_NODISCARD constexpr auto pow(float base, float exp) -> float
{
    MC_IF_CONSTEVAL { return gcem::pow(base, exp); }
    return std::pow(base, exp);
}

MC_NODISCARD constexpr auto pow(double base, double exp) -> double
{
    MC_IF_CONSTEVAL { return gcem::pow(base, exp); }
    return std::pow(base, exp);
}
}  // namespace mc
