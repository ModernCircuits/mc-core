#pragma once

#include "mc/stdexcept.hpp"
#include "mc/utility.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto splitColumns(Matrix const& mat, typename Matrix::size_type colIdx) -> std::pair<Matrix, Matrix>
{
    using size_type = typename Matrix::size_type;

    if (colIdx >= mat.cols()) { throw std::out_of_range("column index out of bounds"); }

    auto const numRows = mat.rows();
    auto const numColA = colIdx;
    auto const numColB = mat.cols() - colIdx;

    auto a = Matrix { numRows, numColA };
    auto b = Matrix { numRows, numColB };

    for (size_type row = 0; row < numRows; ++row) {
        for (size_type col = 0; col < mat.cols(); ++col) {
            if (col < colIdx) {
                a(row, col) = mat(row, col);
            } else {
                b(row, col - colIdx) = mat(row, col);
            }
        }
    }

    return std::make_pair(a, b);
}
} // namespace math
} // namespace mc
