#pragma once

#include <limits>

#include "xorshift32.hpp"

namespace mc {

template<typename T>
constexpr BasicXorShift32<T>::BasicXorShift32(result_type seed) noexcept
    : _state{seed}
{}

template<typename T>
constexpr auto BasicXorShift32<T>::min() noexcept -> result_type
{
    return std::numeric_limits<uint32_t>::min();
}

template<typename T>
constexpr auto BasicXorShift32<T>::max() noexcept -> result_type
{
    return std::numeric_limits<uint32_t>::max() - 1U;
}

template<typename T>
constexpr auto BasicXorShift32<T>::seed(result_type value) noexcept -> void
{
    _state = value;
}

template<typename T>
constexpr auto BasicXorShift32<T>::discard(unsigned long long z) noexcept
    -> void
{
    for (auto i{0ULL}; i < z; ++i) { (void)((*this)()); }
}

template<typename T>
constexpr auto BasicXorShift32<T>::operator()() noexcept -> result_type
{
    _state ^= _state << uint32_t(13);
    _state ^= _state >> uint32_t(17);
    _state ^= _state << uint32_t(5);
    return _state;
}

template<typename T>
constexpr auto operator==(
    BasicXorShift32<T> const& lhs,
    BasicXorShift32<T> const& rhs
) noexcept -> bool
{
    return lhs._state == rhs._state;
}

template<typename T>
constexpr auto operator!=(
    BasicXorShift32<T> const& lhs,
    BasicXorShift32<T> const& rhs
) noexcept -> bool
{
    return !(lhs == rhs);
}

}  // namespace mc
