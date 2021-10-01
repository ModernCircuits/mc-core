#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_optional)
#include <optional>
namespace mc {
using std::optional;
} // namespace mc
#else
#include "boost/optional.hpp"
namespace mc {
using boost::optional;
} // namespace mc
#endif