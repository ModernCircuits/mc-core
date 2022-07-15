#pragma once

#include "mc/math/matrix/detail/matrixAdd.hpp"
#include "mc/math/matrix/detail/matrixCompare.hpp"
#include "mc/math/matrix/detail/matrixMultiply.hpp"
#include "mc/math/matrix/detail/matrixStream.hpp"
#include "mc/math/matrix/detail/matrixSubscriptToIndex.hpp"
#include "mc/math/matrix/detail/matrixSubtract.hpp"
#include "mc/math/traits/IsMatrix.hpp"
#include "mc/math/traits/IsVector.hpp"
#include "mc/type_traits.hpp"

namespace mc {
namespace math {

template <typename Matrix>
auto operator==(Matrix const& l, Matrix const& r) -> std::enable_if_t<IsMatrix<Matrix>::value, bool>
{
    return detail::matrixEqual(l, r);
}

template <typename Matrix>
auto operator!=(Matrix const& l, Matrix const& r) -> std::enable_if_t<IsMatrix<Matrix>::value, bool>
{
    return detail::matrixNotEqual(l, r);
}

template <typename Matrix>
auto operator+(Matrix const& l, Matrix const& r) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixAdd(l, r);
}

template <typename Matrix>
auto operator+(Matrix const& m, typename Matrix::value_type scaler) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixAdd(m, scaler);
}

template <typename Matrix>
auto operator+(typename Matrix::value_type scaler, Matrix const& m) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixAdd(m, scaler);
}

template <typename Matrix>
auto operator-(Matrix const& l, Matrix const& r) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixSubtract(l, r);
}

template <typename Matrix>
auto operator-(Matrix const& m, typename Matrix::value_type scaler) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixSubtract(m, scaler);
}

template <typename Matrix>
auto operator-(typename Matrix::value_type scaler, Matrix const& m) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixSubtract(m, scaler);
}

template <typename Matrix>
auto operator*(Matrix const& m, typename Matrix::value_type scaler) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixMultiply(m, scaler);
}

template <typename Matrix>
auto operator*(typename Matrix::value_type scaler, Matrix const& m) -> std::enable_if_t<IsMatrix<Matrix>::value, Matrix>
{
    return detail::matrixMultiply(m, scaler);
}

template <typename Matrix, typename Vector>
auto operator*(Matrix const& mat, Vector const& vec)
    -> std::enable_if_t<IsMatrix<Matrix>::value && IsVector<Vector>::value, Vector>
{
    return detail::matrixMultiplyWithVector(mat, vec);
}

template <typename Matrix>
auto operator<<(std::ostream& out, Matrix const& m) -> std::enable_if_t<IsMatrix<Matrix>::value, std::ostream&>
{
    return detail::matrixOutStream(out, m);
}

} // namespace math
} // namespace mc