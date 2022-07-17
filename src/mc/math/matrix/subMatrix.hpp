#pragma once

#include "mc/math/traits/IsMatrix.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto subMatrix(Matrix const& mat, typename Matrix::size_type rowIdx, typename Matrix::size_type colIdx)
    -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    auto result = Matrix { mat.rows() - 1, mat.cols() - 1 };
    for (decltype(mat.rows()) row = 0; row < mat.rows(); ++row) {
        for (decltype(mat.rows()) col = 0; col < mat.cols(); ++col) {
            if ((row != rowIdx) && (col != colIdx)) {
                auto newRow            = row < rowIdx ? row : row - 1;
                auto newCol            = col < colIdx ? col : col - 1;
                result(newRow, newCol) = mat(row, col);
            }
        }
    }
    return result;
}

} // namespace math
} // namespace mc
