// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_optional)
#include <optional>

namespace mc {
template<typename T>
using Optional = std::optional<T>;

using NullOpt = std::nullopt_t;

using std::nullopt;
}  // namespace mc
#else
#include <boost/optional.hpp>

namespace mc {
template<typename T>
using Optional = boost::optional<T>;

using NullOpt = boost::none_t;

// NOLINTNEXTLINE(readability-identifier-naming)
constexpr auto const nullopt = boost::none;
}  // namespace mc
#endif
