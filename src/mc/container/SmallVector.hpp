#pragma once

#include "boost/container/small_vector.hpp"

namespace mc {
template <typename T, std::size_t InlineCapacity>
using SmallVector = boost::container::small_vector<T, InlineCapacity>;
}