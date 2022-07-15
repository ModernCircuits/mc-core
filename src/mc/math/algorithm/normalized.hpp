#pragma once

#include "mc/math/algorithm/norm.hpp"

namespace mc {
namespace math {

template <typename VectorT>
auto normalized(VectorT const& v) noexcept -> VectorT
{
    using T = typename VectorT::value_type;
    return VectorT { v } * (T { 1 } / norm(v));
}

} // namespace math
} // namespace mc