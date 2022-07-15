#pragma once

#include "mc/units/fwd/TreatAsFloatingPoint.hpp"

#include "mc/type_traits.hpp"

namespace mc {
template <typename Rep>
struct TreatAsFloatingPoint : std::is_floating_point<Rep> {
};
} // namespace mc