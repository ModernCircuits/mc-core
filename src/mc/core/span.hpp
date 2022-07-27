// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <boost/core/span.hpp>

namespace mc {
using boost::dynamic_extent;
using boost::span;

#if defined(__cpp_lib_byte)
using boost::as_bytes;
using boost::as_writable_bytes;
#endif
}  // namespace mc
