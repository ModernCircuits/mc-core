// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_clamp)
    #include <algorithm>
namespace mc {
using std::clamp;
}
#else
    #include <boost/algorithm/clamp.hpp>
namespace mc {
using boost::algorithm::clamp;
} // namespace mc
#endif
