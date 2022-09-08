#pragma once

#include <mc/core/config.hpp>

#include <cstdint>

namespace mc {

template<typename T>
struct BasicXorShift32
{
    // NOLINTNEXTLINE(readability-identifier-naming)
    using result_type = T;

    // NOLINTNEXTLINE(readability-identifier-naming)
    static constexpr auto default_seed = result_type{42};

    constexpr BasicXorShift32() = default;
    explicit constexpr BasicXorShift32(result_type seed) noexcept;

    MC_NODISCARD static constexpr auto min() noexcept -> result_type;
    MC_NODISCARD static constexpr auto max() noexcept -> result_type;

    constexpr auto seed(result_type value = default_seed) noexcept -> void;
    constexpr auto discard(unsigned long long z) noexcept -> void;

    MC_NODISCARD constexpr auto operator()() noexcept -> result_type;

    template<typename U>
    friend constexpr auto operator==(
        BasicXorShift32<U> const& lhs,
        BasicXorShift32<U> const& rhs
    ) noexcept -> bool;

    template<typename U>
    friend constexpr auto operator!=(
        BasicXorShift32<U> const& lhs,
        BasicXorShift32<U> const& rhs
    ) noexcept -> bool;

private:
    result_type _state{default_seed};
};

using XorShift32 = BasicXorShift32<std::uint32_t>;

}  // namespace mc

#include "xorshift32.impl.hpp"
