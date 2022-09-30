// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <tl/expected.hpp>

namespace mc {

template<typename T, typename E>
using Expected = tl::expected<T, E>;

}  // namespace mc
