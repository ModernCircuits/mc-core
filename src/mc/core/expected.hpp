// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <tl/expected.hpp>

namespace mc {
template<typename T, typename E>
using Expected = tl::expected<T, E>;

template<typename E>
using Unexpected = tl::unexpected<E>;

template<typename E>
[[nodiscard]] constexpr auto makeUnexpected(E&& e)
    -> decltype(tl::make_unexpected(std::forward<E>(e)))
{
    return tl::make_unexpected(std::forward<E>(e));
}

using tl::unexpect;
using tl::unexpect_t;

template<typename E>
using BadExpectedAccess = tl::bad_expected_access<E>;

}  // namespace mc
