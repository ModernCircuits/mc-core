#pragma once

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto multiplyAddRow(Matrix& mat, typename Matrix::size_type src,
    typename Matrix::size_type dest, typename Matrix::value_type factor) -> void
{
    if ((src >= mat.rows()) || (src >= mat.rows())) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        mat(dest, col) += mat(src, col) * factor;
    }
}

} // namespace math
} // namespace mc