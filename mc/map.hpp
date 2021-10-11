#pragma once

#include <map>

#include "container/FlatMap.hpp"

#if defined(__cpp_lib_memory_resource)
namespace mc {
namespace pmr {
using std::pmr::map;
} // namespace pmr
} // namespace mc
#else
    #include "boost/container/pmr/map.hpp"
namespace mc {
namespace pmr {
using boost::container::pmr::map;
} // namespace pmr
} // namespace mc

#endif