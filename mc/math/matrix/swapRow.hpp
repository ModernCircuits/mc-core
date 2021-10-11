#pragma once

#include "mc/stdexcept.hpp"
#include "mc/utility.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto swapRow(Matrix& mat, typename Matrix::size_type a,
    typename Matrix::size_type b) -> void
{
    if ((a >= mat.rows()) || (b >= mat.rows())) {
        throw std::out_of_range("row index out of bounds");
    }

    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        using std::swap;
        swap(mat(a, col), mat(b, col));
    }
}
} // namespace math
} // namespace mc