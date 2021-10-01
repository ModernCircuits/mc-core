#pragma once

#include "boost/container/static_vector.hpp"

namespace lt {
template <typename T, std::size_t Capacity>
using StaticVector = boost::container::static_vector<T, Capacity>;
}