
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_parallel_algorithm)
    #include <numeric>
namespace mc {
using std::transform_reduce;
}
#else
    #include <boost/algorithm/cxx17/transform_reduce.hpp>
namespace mc {
using boost::algorithm::transform_reduce;
} // namespace mc
#endif
