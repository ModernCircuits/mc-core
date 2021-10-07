#pragma once

#include "mc/chrono.hpp"
#include "mc/config.hpp"

namespace mc {

/// \brief Duration.
template <typename T, typename R>
using Duration = std::chrono::duration<T, R>;

/// \brief Duration in microseconds.
template <typename T>
using Microseconds = Duration<T, std::micro>;

/// \brief Duration in milliseconds.
template <typename T>
using Milliseconds = Duration<T, std::milli>;

/// \brief Duration in seconds.
template <typename T>
using Seconds = Duration<T, std::ratio<1>>;

/// \brief Converts a duration to milliseconds.
template <typename T, typename R>
MC_NODISCARD constexpr auto toMilliseconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Milliseconds<T>>(d);
}

/// \brief Converts a duration to seconds.
template <typename T, typename R>
MC_NODISCARD constexpr auto toSeconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Seconds<T>>(d);
}

} // namespace mc