#pragma once

#include "mc/ratio.hpp"

namespace mc {

/// \brief Type for handling frequencies.
///
/// \code{.cpp}
/// using Hertz     = mc::Hertz<float>;
/// using Kilohertz = mc::Kilohertz<float>;
/// using BPM       = mc::BPM<float>;
///
/// static_assert(mc::frequencyCast<BPM>(Hertz(1)).count()         == 60);
/// static_assert(mc::frequencyCast<Hertz>(Kilohertz(1)).count()   == 1000);
/// \endcode
///
/// \ingroup group-units
template <typename Rep, typename Period = std::ratio<1>>
struct Frequency;

} // namespace mc