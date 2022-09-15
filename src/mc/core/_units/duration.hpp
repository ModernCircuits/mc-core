// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/chrono.hpp>

namespace mc {

/// \brief Duration.
/// \ingroup group-units
template<typename T, typename R>
using Duration = std::chrono::duration<T, R>;

/// \brief Duration in microseconds.
/// \ingroup group-units
template<typename T>
using Microseconds = Duration<T, std::micro>;

/// \brief Duration in milliseconds.
/// \ingroup group-units
template<typename T>
using Milliseconds = Duration<T, std::milli>;

/// \brief Duration in seconds.
/// \ingroup group-units
template<typename T>
using Seconds = Duration<T, std::ratio<1>>;

/// \brief Converts a duration to milliseconds.
/// \ingroup group-units
template<typename T, typename R>
[[nodiscard]] constexpr auto toMilliseconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Milliseconds<T>>(d);
}

/// \brief Converts a duration to seconds.
/// \ingroup group-units
template<typename T, typename R>
[[nodiscard]] constexpr auto toSeconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Seconds<T>>(d);
}

}  // namespace mc
