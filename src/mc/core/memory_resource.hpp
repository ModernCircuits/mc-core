// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#include <boost/container/pmr/global_resource.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/pmr/monotonic_buffer_resource.hpp>
#include <boost/container/pmr/synchronized_pool_resource.hpp>
#include <boost/container/pmr/unsynchronized_pool_resource.hpp>

namespace mc {
namespace pmr {
using boost::container::pmr::get_default_resource;
using boost::container::pmr::memory_resource;
using boost::container::pmr::monotonic_buffer_resource;
using boost::container::pmr::new_delete_resource;
using boost::container::pmr::null_memory_resource;
using boost::container::pmr::polymorphic_allocator;
using boost::container::pmr::pool_options;
using boost::container::pmr::set_default_resource;
using boost::container::pmr::synchronized_pool_resource;
using boost::container::pmr::unsynchronized_pool_resource;
} // namespace pmr
} // namespace mc
