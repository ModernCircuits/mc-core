// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <tl/expected.hpp>

namespace mc {

template<typename E>
using BadExpectedAccess = tl::bad_expected_access<E>;

}  // namespace mc
