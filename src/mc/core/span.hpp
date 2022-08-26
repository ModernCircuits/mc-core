// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_span)

#include <span>

namespace mc {
using std::dynamic_extent;
using std::span;

#if defined(__cpp_lib_byte)
using std::as_bytes;
using std::as_writable_bytes;
#endif
}  // namespace mc

#else

#include <boost/core/span.hpp>

namespace mc {
using boost::dynamic_extent;
using boost::span;

#if defined(__cpp_lib_byte)
using boost::as_bytes;
using boost::as_writable_bytes;
#endif
}  // namespace mc

#endif
