#pragma once

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto multiplyRow(Matrix& mat, typename Matrix::size_type row,
    typename Matrix::value_type factor) -> void
{
    if (row >= mat.rows()) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        mat(row, col) *= factor;
    }
}
} // namespace math
} // namespace mc