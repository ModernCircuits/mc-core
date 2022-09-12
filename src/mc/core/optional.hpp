// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <tl/optional.hpp>

namespace mc {

template<typename T>
using Optional = tl::optional<T>;
using NullOpt  = tl::nullopt_t;
using tl::nullopt;

}  // namespace mc
