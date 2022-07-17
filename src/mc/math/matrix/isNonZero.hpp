#pragma once

#include "mc/config.hpp"
#include "mc/math/algorithm/approx.hpp"

namespace mc {
namespace math {
template <typename Matrix>
MC_NODISCARD auto isNonZero(Matrix const& mat) -> bool
{
    using T = typename Matrix::value_type;
    for (decltype(mat.rows()) row { 0 }; row < mat.rows(); ++row) {
        for (decltype(mat.cols()) col { 0 }; col < mat.cols(); ++col) {
            if (!approx(mat(row, col), T {})) { return true; }
        }
    }
    return false;
}
} // namespace math
} // namespace mc
