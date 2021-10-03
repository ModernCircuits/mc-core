#pragma once

#include "mc/version.hpp"

#if defined(__cpp_lib_optional)
#include <optional>
namespace mc {
using std::make_optional;
using std::optional;
using nullopt_t = std::nullopt_t;

constexpr auto const nullopt = std::nullopt; // NOLINT(readability-identifier-naming)
} // namespace mc
#else
#include "boost/optional.hpp"
namespace mc {
using boost::make_optional;
using boost::optional;
using nullopt_t = boost::none_t;

constexpr auto const nullopt = boost::none; // NOLINT(readability-identifier-naming)
} // namespace mc
#endif