#pragma once

#include "mc/config.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
namespace detail {

template <typename Matrix>
MC_NODISCARD auto matrixSubtract(Matrix const& lhs, Matrix const& rhs) -> Matrix
{
    if ((lhs.rows() != rhs.rows()) || lhs.cols() != rhs.cols()) {
        throw std::invalid_argument("matrix layout must match");
    }

    auto tmp = Matrix { lhs.rows(), lhs.cols() };
    for (decltype(tmp.rows()) row = 0; row < lhs.rows(); ++row) {
        for (decltype(tmp.cols()) col = 0; col < rhs.cols(); ++col) {
            tmp(row, col) = lhs(row, col) - rhs(row, col);
        }
    }

    return tmp;
}

template <typename Matrix>
MC_NODISCARD auto matrixSubtract(
    Matrix const& m, typename Matrix::value_type scaler) -> Matrix
{
    auto tmp = Matrix { m.rows(), m.cols() };
    for (decltype(tmp.rows()) row = 0; row < tmp.rows(); ++row) {
        for (decltype(tmp.cols()) col = 0; col < tmp.cols(); ++col) {
            tmp(row, col) = m(row, col) - scaler;
        }
    }
    return tmp;
}

} // namespace detail
} // namespace math
} // namespace mc
