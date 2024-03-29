// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <boost/container/static_vector.hpp>

namespace mc {

/// \ingroup group-containers
template<typename T, std::size_t Capacity>
using StaticVector = boost::container::static_vector<T, Capacity>;
}  // namespace mc
