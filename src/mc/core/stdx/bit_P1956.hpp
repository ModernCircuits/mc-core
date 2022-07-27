// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if __has_include(<bit>)
#include <bit>
#endif

#if defined(__cpp_lib_int_pow2)
namespace mc {
using std::bit_ceil;
using std::bit_floor;
using std::bit_width;
using std::has_single_bit;
}  // namespace mc
#else
#include <boost/core/bit.hpp>

namespace mc {
using boost::core::bit_ceil;
using boost::core::bit_floor;
using boost::core::bit_width;
using boost::core::has_single_bit;
}  // namespace mc
#endif
