#pragma once

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto findRowWithMaxElement(Matrix const& mat, typename Matrix::size_type col,
    typename Matrix::size_type startRow) -> typename Matrix::size_type
{
    if (startRow >= mat.rows()) {
        throw std::out_of_range("row index out of bounds");
    }
    if (col >= mat.cols()) {
        throw std::out_of_range("column index out of bounds");
    }

    auto maxId = startRow;
    for (auto row = startRow; row < mat.rows(); ++row) {
        if (mat(row, col) >= mat(maxId, col)) { maxId = row; }
    }

    return maxId;
}
} // namespace math
} // namespace mc