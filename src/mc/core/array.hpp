// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <array>
#include <cstddef>

namespace mc {

/// \ingroup group-containers
template<typename T, std::size_t Size>
using Array = std::array<T, Size>;

}  // namespace mc
