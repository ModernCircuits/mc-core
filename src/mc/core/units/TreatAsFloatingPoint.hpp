#pragma once

#include "mc/core/units/fwd/TreatAsFloatingPoint.hpp"

#include "mc/core/type_traits.hpp"

namespace mc {
template <typename Rep>
struct TreatAsFloatingPoint : std::is_floating_point<Rep> {
};
} // namespace mc
