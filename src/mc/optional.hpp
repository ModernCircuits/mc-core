#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_optional)
    #include <optional>
namespace mc {
using std::make_optional;
using std::nullopt;
using std::nullopt_t;
using std::optional;
} // namespace mc
#else
    #include <boost/optional.hpp>
namespace mc {
using boost::make_optional;
using boost::optional;
using nullopt_t = boost::none_t;

// NOLINTNEXTLINE(readability-identifier-naming)
constexpr auto const nullopt = boost::none;
} // namespace mc
#endif
