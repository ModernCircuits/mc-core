// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <boost/container/flat_map.hpp>

namespace mc {

/// \ingroup group-containers
template<
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename AllocatorOrContainer
    = boost::container::new_allocator<std::pair<Key, T>>>
using FlatMap
    = boost::container::flat_map<Key, T, Compare, AllocatorOrContainer>;

}  // namespace mc
