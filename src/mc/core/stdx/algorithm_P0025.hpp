#pragma once

#include "mc/core/version.hpp"

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
