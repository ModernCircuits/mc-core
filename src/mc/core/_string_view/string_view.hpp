// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_string_view)
#include <string_view>

namespace mc {

/// \ingroup group-strings
using StringView = std::string_view;

}  // namespace mc
#else
#include <boost/utility/string_view.hpp>

namespace mc {

/// \ingroup group-strings
using StringView = boost::string_view;

}  // namespace mc
#endif
