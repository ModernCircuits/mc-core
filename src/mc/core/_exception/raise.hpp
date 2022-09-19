// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <fmt/format.h>

#include <exception>
#include <utility>

namespace mc {

template<typename E, typename... Args>
[[noreturn]] MC_COLD MC_NO_INLINE constexpr auto raise(Args&&... args) -> void
{
    throw E{std::forward<Args>(args)...};
}

template<typename E, typename... Args>
[[noreturn]] MC_COLD MC_NO_INLINE constexpr auto
raisef(::fmt::format_string<Args...> str, Args&&... args) -> void
{
    throw E{fmt::format(str, std::forward<Args>(args)...)};
}

}  // namespace mc
