#pragma once

#include "mc/math/matrix/isSquare.hpp"

#include "mc/stdexcept.hpp"

namespace mc {
namespace math {

template <typename Matrix>
auto makeIdentity(Matrix& mat) -> void
{
    if (!isSquare(mat)) { throw std::invalid_argument("matrix must be square"); }

    mat.clear();
    for (decltype(mat.rows()) i = 0; i < mat.rows(); ++i) { mat(i, i) = typename Matrix::value_type { 1 }; }
}

template <typename Matrix>
auto makeIdentity(typename Matrix::size_type size) -> Matrix
{
    auto mat = Matrix { size, size };
    makeIdentity(mat);
    return mat;
}

} // namespace math
} // namespace mc