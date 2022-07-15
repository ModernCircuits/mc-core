#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_string_view)
    #include <string_view>
namespace mc {
using std::string_view;
} // namespace mc
#else
    #include "boost/utility/string_view.hpp"
namespace mc {
using boost::string_view;
} // namespace mc
#endif