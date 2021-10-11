#pragma once

#include "mc/config.hpp"

namespace mc {
namespace math {
namespace detail {

template <typename Matrix>
MC_NODISCARD auto matrixEqual(Matrix const& lhs, Matrix const& rhs) -> bool
{
    if ((lhs.rows() != rhs.rows()) || (lhs.cols() != rhs.cols())) {
        return false;
    }
    for (decltype(lhs.rows()) row = 0; row < lhs.rows(); ++row) {
        for (decltype(lhs.cols()) col = 0; col < lhs.cols(); ++col) {
            if (lhs(row, col) != rhs(row, col)) { return false; }
        }
    }
    return true;
}

template <typename Matrix>
MC_NODISCARD auto matrixNotEqual(Matrix const& lhs, Matrix const& rhs) -> bool
{
    return !matrixEqual(lhs, rhs);
}

} // namespace detail
} // namespace math
} // namespace mc