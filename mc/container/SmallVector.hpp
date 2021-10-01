#pragma once

#include "boost/container/small_vector.hpp"

namespace lt {
template <typename T, std::size_t InlineCapacity>
using SmallVector = boost::container::small_vector<T, InlineCapacity>;
}