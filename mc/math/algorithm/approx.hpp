#pragma once

#include "mc/cmath.hpp"
#include "mc/config.hpp"
#include "mc/limits.hpp"

namespace mc {
namespace math {
template <typename T>
MC_NODISCARD auto approx(T a, T b) -> bool
{
    return std::abs(a - b) < (std::numeric_limits<T>::epsilon() * T { 16 });
}
} // namespace math
} // namespace mc