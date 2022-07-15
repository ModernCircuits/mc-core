#pragma once

namespace mc {

/// \brief This trait helps determine if a duration can be
/// converted to another duration with a different tick period.
///
/// \details Implicit conversions between two durations normally depends on the
/// tick period of the durations. However, implicit conversions can happen
/// regardless of tick period if `TreatAsFloatingPoint<Rep>::value == true`.
///
/// \ingroup group-units
template <typename Rep>
struct TreatAsFloatingPoint;

} // namespace mc