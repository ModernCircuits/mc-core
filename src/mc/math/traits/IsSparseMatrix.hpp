#pragma once

#include "mc/type_traits.hpp"

namespace mc {
namespace math {
template <typename T>
struct IsSparseMatrix : FalseType {
};
} // namespace math
} // namespace mc
