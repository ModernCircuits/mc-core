
#pragma once

#include "mc/config.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
namespace detail {

template <typename Matrix>
MC_NODISCARD auto matrixMultiply(Matrix const& m, typename Matrix::value_type scaler) -> Matrix
{
    auto tmp = Matrix { m.rows(), m.cols() };
    for (decltype(tmp.rows()) row = 0; row < tmp.rows(); ++row) {
        for (decltype(tmp.cols()) col = 0; col < tmp.cols(); ++col) { tmp(row, col) = m(row, col) * scaler; }
    }
    return tmp;
}
template <typename Matrix, typename Vector>
MC_NODISCARD auto matrixMultiplyWithVector(Matrix const& mat, Vector const& vec) -> Vector
{
    if (mat.cols() != vec.size()) { throw std::domain_error("matrix columns and vector size must match"); }

    auto result = Vector { vec };
    for (decltype(mat.rows()) row = 0; row < mat.rows(); ++row) {
        auto sum = typename Vector::value_type {};
        for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) { sum += mat(row, col) * vec[col]; }
        result[row] = sum;
    }

    return result;
}

} // namespace detail
} // namespace math
} // namespace mc
