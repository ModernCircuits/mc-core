// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <bitset>
#include <cstddef>

namespace mc {
template<std::size_t NumBits>
using BitSet = std::bitset<NumBits>;
}
