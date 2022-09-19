// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <cstddef>

#include <type_traits>

namespace mc {
using ssize_t = std::make_signed_t<std::size_t>;
}  // namespace mc
