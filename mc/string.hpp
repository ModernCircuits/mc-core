#pragma once

#include <string>

#if defined(__cpp_lib_memory_resource)

namespace mc {
namespace pmr {
    using std::pmr::string;
} // namespace pmr
} // namespace mc

#else

#include "boost/container/pmr/string.hpp"

namespace mc {
namespace pmr {
    using boost::container::pmr::string;
} // namespace pmr
} // namespace mc

#endif