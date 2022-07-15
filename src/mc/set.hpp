#pragma once

#include <set>

#include "container/FlatSet.hpp"

#if defined(__cpp_lib_memory_resource)

namespace mc {
namespace pmr {
using std::pmr::set;
} // namespace pmr
} // namespace mc

#else
    #include "boost/container/pmr/set.hpp"
namespace mc {
namespace pmr {
using boost::container::pmr::set;
} // namespace pmr
} // namespace mc

#endif