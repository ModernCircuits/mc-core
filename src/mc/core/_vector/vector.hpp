// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <vector>

namespace mc {

/// \ingroup group-containers
template<typename T, typename Alloc = std::allocator<T> >
using Vector = std::vector<T, Alloc>;

}  // namespace mc
