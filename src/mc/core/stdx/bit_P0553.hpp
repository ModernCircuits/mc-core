// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_bitops)
#include <bit>

namespace mc {
using std::countl_one;
using std::countl_zero;
using std::countr_one;
using std::countr_zero;
using std::popcount;
using std::rotl;
using std::rotr;
}  // namespace mc
#else
// Boost via Emscripten is at 1.75. Bit header missing
#if __has_include(<boost/core/bit.hpp>)
#include <boost/core/bit.hpp>

namespace mc {
using boost::core::countl_one;
using boost::core::countl_zero;
using boost::core::countr_one;
using boost::core::countr_zero;
using boost::core::popcount;
using boost::core::rotl;
using boost::core::rotr;
}  // namespace mc
#endif
#endif
