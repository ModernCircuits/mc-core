#pragma once

#include "mc/math/matrix/isSquare.hpp"
#include "mc/math/matrix/subMatrix.hpp"
#include "mc/math/traits/IsMatrix.hpp"
#include "mc/stdexcept.hpp"

namespace mc {
namespace math {
template <typename Matrix>
auto determinant(Matrix const& mat) -> std::enable_if_t<IsMatrix<Matrix>::value, typename Matrix::value_type>
{
    using value_type = typename Matrix::value_type;

    if (!isSquare(mat)) { throw std::invalid_argument("matrix must be square"); }

    if (mat.rows() == 2) { return (mat(0, 0) * mat(1, 1)) - (mat(0, 1) * mat(1, 0)); }

    auto sum  = value_type { 0 };
    auto sign = value_type { 1 };
    for (decltype(mat.cols()) col = 0; col < mat.cols(); ++col) {
        auto sub = subMatrix(mat, 0, col);
        auto d   = determinant(sub);
        sum += mat(0, col) * d * sign;
        sign = -sign;
    }

    return sum;
}
} // namespace math
} // namespace mc
