#pragma once

#include "mc/version.hpp"

#if 0
    #if defined(__cpp_lib_filesystem)
        #include <filesystem>
namespace mc {
namespace filesystem = std::filesystem;
} // namespace mc
    #else
        #include <boost/filesystem.hpp>
namespace mc {
namespace filesystem = boost::filesystem;
} // namespace mc
    #endif

#endif