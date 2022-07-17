#pragma once

#include "mc/math/algorithm/norm.hpp"

#include "mc/algorithm.hpp"

namespace mc {
namespace math {
template <typename VectorT>
auto normalize(VectorT& vec) noexcept -> void
{
    using T         = typename VectorT::value_type;
    auto const func = [n = norm(vec)](auto v) { return v * (T(1) / n); };
    std::transform(vec.begin(), vec.end(), vec.begin(), func);
}
} // namespace math
} // namespace mc
