#pragma once

#if defined(__cpp_lib_string_view) && __cplusplus > 201402L
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