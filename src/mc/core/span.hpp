// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#if defined(__cpp_lib_span)

#include <span>

namespace mc {
/// \ingroup group-containers
MC_INLINE_VAR constexpr auto DynamicExtent = std::dynamic_extent;

/// \ingroup group-containers
template<typename T, std::size_t Extent = DynamicExtent>
using Span = std::span<T, Extent>;

#if defined(__cpp_lib_byte)
using std::as_bytes;
using std::as_writable_bytes;
#endif
}  // namespace mc

#else

#include <boost/core/span.hpp>

namespace mc {
/// \ingroup group-containers
MC_INLINE_VAR constexpr auto DynamicExtent = boost::dynamic_extent;

/// \ingroup group-containers
template<typename T, std::size_t Extent = DynamicExtent>
using Span = boost::span<T, Extent>;

#if defined(__cpp_lib_byte)
using boost::as_bytes;
using boost::as_writable_bytes;
#endif
}  // namespace mc

#endif
