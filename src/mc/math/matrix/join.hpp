#pragma once

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto join(Matrix const& a, Matrix const& b) -> Matrix
{
    if (a.rows() != b.rows()) { throw std::invalid_argument("rows size must match"); }

    auto result = Matrix { a.rows(), a.cols() + b.cols() };
    for (typename Matrix::size_type row = 0; row < result.rows(); ++row) {
        for (typename Matrix::size_type col = 0; col < result.cols(); ++col) {
            auto const& source   = col < a.cols() ? a : b;
            auto const sourceCol = col < a.cols() ? col : col - a.cols();
            result(row, col)     = source(row, sourceCol);
        }
    }
    return result;
}

} // namespace math
} // namespace mc