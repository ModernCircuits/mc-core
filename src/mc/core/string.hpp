// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <boost/container/pmr/string.hpp>

#include <string>

namespace mc {

using String = std::string;

namespace pmr {
using String = boost::container::pmr::string;
}  // namespace pmr
}  // namespace mc
