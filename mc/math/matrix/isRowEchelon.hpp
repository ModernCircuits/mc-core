#pragma once

#include "mc/config.hpp"
#include "mc/math/algorithm/approx.hpp"

namespace mc {
namespace math {
template <typename Matrix>
MC_NODISCARD constexpr auto isRowEchelon(Matrix const& mat) -> bool
{
    using T  = typename Matrix::value_type;
    auto sum = T {};
    for (decltype(mat.rows()) row { 1 }; row < mat.rows(); ++row) {
        for (decltype(mat.cols()) col { 0 }; col < row; ++col) { sum += mat(row, col); }
    }
    return approx(sum, T {});
}
} // namespace math
} // namespace mc