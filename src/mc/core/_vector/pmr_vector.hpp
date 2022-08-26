// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <boost/container/pmr/vector.hpp>

namespace mc {
namespace pmr {
template<typename T>
using Vector = boost::container::pmr::vector<T>;
}  // namespace pmr
}  // namespace mc
