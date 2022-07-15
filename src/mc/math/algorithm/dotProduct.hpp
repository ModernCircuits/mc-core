#pragma once

#include "mc/numeric.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {

template <typename VectorT>
auto dotProduct(VectorT const& l, VectorT const& r) -> typename VectorT::value_type
{
    using T = typename VectorT::value_type;
    if (l.size() != r.size()) { throw std::domain_error("vectors need to be the same size"); }
    return mc::transform_reduce(l.begin(), l.end(), r.begin(), T {});
}
} // namespace math
} // namespace mc