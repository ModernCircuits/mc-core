#pragma once

#include "mc/math/traits/IsDenseMatrix.hpp"
#include "mc/math/traits/IsSparseMatrix.hpp"

namespace mc {
namespace math {
template <typename T>
struct IsMatrix
    : BoolConstant<IsDenseMatrix<T>::value || IsSparseMatrix<T>::value> {
};
} // namespace math
} // namespace mc