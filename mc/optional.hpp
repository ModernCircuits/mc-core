#pragma once

#if __has_include(<optional>) && __cplusplus > 201402L
#include <optional>
#endif

#if defined(__cpp_lib_optional)
namespace mc {
using std::optional;
} // namespace mc
#else
#include "boost/optional.hpp"
namespace mc {
using boost::optional;
} // namespace mc
#endif