#pragma once

#include "mc/version.hpp"

#include <vector>

#include "container/SmallVector.hpp"
#include "container/StaticVector.hpp"

#if defined(__cpp_lib_memory_resource)

namespace mc {
namespace pmr {
    using std::pmr::vector;
} // namespace pmr
} // namespace mc

#else

#include "boost/container/pmr/vector.hpp"

namespace mc {
namespace pmr {
    using boost::container::pmr::vector;
} // namespace pmr
} // namespace mc

#endif