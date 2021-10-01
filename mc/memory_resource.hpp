#pragma once

#if __has_include(<memory_resource>) && __cplusplus > 201402L
#include <memory_resource>
#endif

#if defined(__cpp_lib_memory_resource)

namespace mc {
namespace pmr {
    using std::pmr::get_default_resource;
    using std::pmr::memory_resource;
    using std::pmr::monotonic_buffer_resource;
    using std::pmr::new_delete_resource;
    using std::pmr::null_memory_resource;
    using std::pmr::polymorphic_allocator;
    using std::pmr::pool_options;
    using std::pmr::set_default_resource;
    using std::pmr::synchronized_pool_resource;
    using std::pmr::unsynchronized_pool_resource;
} // namespace pmr
} // namespace mc

#else

#include "boost/container/pmr/global_resource.hpp"
#include "boost/container/pmr/memory_resource.hpp"
#include "boost/container/pmr/monotonic_buffer_resource.hpp"
#include "boost/container/pmr/synchronized_pool_resource.hpp"
#include "boost/container/pmr/unsynchronized_pool_resource.hpp"

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

#endif