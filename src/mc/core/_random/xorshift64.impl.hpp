#pragma once

#include <limits>

#include "xorshift64.hpp"

namespace mc {

template<typename T>
constexpr BasicXorShift64<T>::BasicXorShift64(result_type seed) noexcept
    : _state{seed}
{}

template<typename T>
constexpr auto BasicXorShift64<T>::min() noexcept -> result_type
{
    return std::numeric_limits<uint64_t>::min();
}

template<typename T>
constexpr auto BasicXorShift64<T>::max() noexcept -> result_type
{
    return std::numeric_limits<uint64_t>::max() - 1UL;
}

template<typename T>
constexpr auto BasicXorShift64<T>::seed(result_type value) noexcept -> void
{
    _state = value;
}

template<typename T>
constexpr auto BasicXorShift64<T>::discard(unsigned long long z) noexcept
    -> void
{
    for (auto i{0ULL}; i < z; ++i) { (void)((*this)()); }
}

template<typename T>
constexpr auto BasicXorShift64<T>::operator()() noexcept -> result_type
{
    _state ^= _state << uint64_t(13);
    _state ^= _state >> uint64_t(7);
    _state ^= _state << uint64_t(17);
    return _state;
}

template<typename T>
constexpr auto operator==(
    BasicXorShift64<T> const& lhs,
    BasicXorShift64<T> const& rhs
) noexcept -> bool
{
    return lhs._state == rhs._state;
}

template<typename T>
constexpr auto operator!=(
    BasicXorShift64<T> const& lhs,
    BasicXorShift64<T> const& rhs
) noexcept -> bool
{
    return !(lhs == rhs);
}

}  // namespace mc
