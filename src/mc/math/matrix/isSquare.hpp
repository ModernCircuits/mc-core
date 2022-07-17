#pragma once

#include "mc/config.hpp"

namespace mc {
namespace math {
template <typename Matrix>
MC_NODISCARD constexpr auto isSquare(Matrix const& mat) noexcept -> decltype(mat.rows() == mat.cols())
{
    return mat.rows() == mat.cols();
}
} // namespace math
} // namespace mc
