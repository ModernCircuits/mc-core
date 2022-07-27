// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <boost/container/flat_set.hpp>

namespace mc {
template<
    typename Key,
    typename Compare              = std::less<Key>,
    typename AllocatorOrContainer = boost::container::new_allocator<Key>>
using FlatSet = boost::container::flat_set<Key, Compare, AllocatorOrContainer>;
}  // namespace mc
