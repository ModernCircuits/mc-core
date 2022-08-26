// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/_iterator/nonmember_container_access.hpp>
#include <mc/core/_iterator/ssize.hpp>

#include <iterator>

namespace mc {
using std::begin;
using std::cbegin;
using std::crbegin;
using std::rbegin;

using std::cend;
using std::crend;
using std::end;
using std::rend;
}  // namespace mc
