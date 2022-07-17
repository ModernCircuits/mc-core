#pragma once

#include "mc/cmath.hpp"
#include "mc/numeric.hpp"

namespace mc {
namespace math {
template <typename VectorT>
auto norm(VectorT const& vec) noexcept -> typename VectorT::value_type
{
    using T = typename VectorT::value_type;
    return std::sqrt(std::accumulate(vec.cbegin(), vec.cend(), T {}));
}
} // namespace math
} // namespace mc
