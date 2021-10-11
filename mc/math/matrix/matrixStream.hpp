#pragma once

#include "mc/ostream.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto matrixOutStream(std::ostream& out, Matrix const& m) -> std::ostream&
{
    for (typename Matrix::size_type row = 0; row < m.rows(); ++row) {
        for (typename Matrix::size_type col = 0; col < m.cols(); ++col) {
            out << m(row, col) << ' ';
        }
        out << '\n';
    }
    return out;
}
} // namespace math
} // namespace mc