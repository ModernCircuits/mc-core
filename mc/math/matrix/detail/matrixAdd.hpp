#pragma once

#include "mc/config.hpp"
#include "mc/math/traits/IsMatrix.hpp"
#include "mc/stdexcept.hpp"
#include "mc/type_traits.hpp"

namespace mc {
namespace math {
namespace detail {

template <typename Matrix>
auto matrixAdd(Matrix const& l, Matrix const& r, TrueType /*isDense*/) -> Matrix
{
    auto s    = Matrix { l.rows(), l.cols() };
    auto plus = std::plus<typename Matrix::value_type> {};
    std::transform(data(l), data(l) + size(l), data(r), data(s), plus);
    return s;
}

template <typename Matrix>
auto matrixAdd(Matrix const& m, typename Matrix::value_type scaler,
    TrueType /*isDense*/) -> Matrix
{
    auto s    = Matrix { m.rows(), m.cols() };
    auto plus = [scaler](auto v) { return v + scaler; };
    std::transform(data(m), data(m) + size(m), data(s), plus);
    return s;
}

template <typename Matrix>
auto matrixAdd(Matrix const& lhs, Matrix const& rhs, FalseType /*isDense*/)
    -> Matrix
{
    auto tmp = Matrix { lhs.rows(), lhs.cols() };
    for (decltype(tmp.rows()) row = 0; row < lhs.rows(); ++row) {
        for (decltype(tmp.cols()) col = 0; col < rhs.cols(); ++col) {
            tmp(row, col) = lhs(row, col) + rhs(row, col);
        }
    }
    return tmp;
}

template <typename Matrix>
auto matrixAdd(Matrix const& m, typename Matrix::value_type scaler,
    FalseType /*isDense*/) -> Matrix
{
    auto tmp = Matrix { m.rows(), m.cols() };
    for (decltype(tmp.rows()) row = 0; row < tmp.rows(); ++row) {
        for (decltype(tmp.cols()) col = 0; col < tmp.cols(); ++col) {
            tmp(row, col) = m(row, col) + scaler;
        }
    }
    return tmp;
}

template <typename Matrix>
MC_NODISCARD auto matrixAdd(Matrix const& lhs, Matrix const& rhs)
    -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    if ((lhs.rows() != rhs.rows()) || lhs.cols() != rhs.cols()) {
        throw std::invalid_argument("matrix layout must match");
    }
    return matrixAdd(lhs, rhs, IsDenseMatrix<Matrix> {});
}

template <typename Matrix>
MC_NODISCARD auto matrixAdd(Matrix const& m, typename Matrix::value_type scaler)
    -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return matrixAdd(m, scaler, IsDenseMatrix<Matrix> {});
}

} // namespace detail
} // namespace math
} // namespace mc