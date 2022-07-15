#pragma once

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename VectorT>
auto crossProduct(VectorT const& l, VectorT const& r) -> VectorT
{
    if (l.size() != r.size()) { throw std::domain_error("vectors need to be the same size"); }
    if (l.size() != 3) { throw std::domain_error("only 3-dimensional vector supported"); }

    auto result = VectorT { l.size() };
    result[0]   = (l[1] * r[2]) - (l[2] * r[1]);
    result[1]   = (l[0] * r[2]) - (l[2] * r[0]);
    result[2]   = (l[0] * r[1]) - (l[1] * r[0]);
    return result;
}
} // namespace math
} // namespace mc