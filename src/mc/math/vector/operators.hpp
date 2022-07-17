#pragma once

#include "mc/algorithm.hpp"
#include "mc/math/traits/IsVector.hpp"
#include "mc/math/vector/detail/vectorAdd.hpp"
#include "mc/ostream.hpp"
#include "mc/type_traits.hpp"

namespace mc {
namespace math {

template <typename Vector>
MC_NODISCARD auto operator==(Vector const& l, Vector const& r) -> std::enable_if_t<IsVector<Vector>::value, bool>
{
    return std::equal(begin(l), end(l), begin(r), end(r));
}

template <typename Vector>
MC_NODISCARD auto operator!=(Vector const& l, Vector const& r) -> std::enable_if_t<IsVector<Vector>::value, bool>
{
    return !(l == r);
}

template <typename Vector>
MC_NODISCARD auto operator+(Vector const& l, Vector const& r) -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    return detail::vectorAddChecked(l, r);
}

template <typename Vector>
MC_NODISCARD auto operator-(Vector const& l, Vector const& r) -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    using T = typename Vector::value_type;
    if (size(l) != size(r)) { throw std::domain_error("vectors need to be the same size"); }
    auto result = Vector { size(l) };
    std::transform(cbegin(l), cend(l), cbegin(r), begin(result), std::minus<T> {});
    return result;
}

template <typename Vector>
MC_NODISCARD auto operator*(Vector const& vec, typename Vector::value_type const& scaler)
    -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    auto result = Vector { size(vec) };
    std::transform(cbegin(vec), cend(vec), begin(result), [scaler](auto v) { return v * scaler; });
    return result;
}

template <typename Vector>
MC_NODISCARD auto operator*(typename Vector::value_type const& scaler, Vector const& vec)
    -> std::enable_if_t<IsVector<Vector>::value, Vector>
{
    return vec * scaler;
}

template <typename Vector>
auto operator<<(std::ostream& out, Vector const& vec) -> std::enable_if_t<IsVector<Vector>::value, std::ostream&>
{
    for (decltype(size(vec)) i = 0; i < size(vec); ++i) { out << vec[i] << ' '; }
    return out;
}

} // namespace math
} // namespace mc
