#pragma once

#include "mc/config.hpp"
#include "mc/math/traits/IsVector.hpp"
#include "mc/stdexcept.hpp"
#include "mc/type_traits.hpp"

namespace mc {
namespace math {
namespace detail {

template <typename Vector>
MC_NODISCARD auto vectorAdd(Vector const& l, Vector const& r) -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    auto s = Vector { size(l) };
    std::transform(cbegin(l), cend(l), cbegin(r), begin(s), std::plus<> {});
    return s;
}

template <typename Vector>
MC_NODISCARD auto vectorAddChecked(Vector const& l, Vector const& r)
    -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    if (size(l) != size(r)) { throw std::domain_error("vectors need to be the same size"); }
    return vectorAdd(l, r);
}

} // namespace detail
} // namespace math
} // namespace mc