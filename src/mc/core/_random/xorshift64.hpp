// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <mc/core/config.hpp>

#include <cstdint>

namespace mc {

template<typename T>
struct BasicXorShift64
{
    // NOLINTNEXTLINE(readability-identifier-naming)
    using result_type = T;

    // NOLINTNEXTLINE(readability-identifier-naming)
    static constexpr auto default_seed = result_type{42};

    constexpr BasicXorShift64() = default;
    explicit constexpr BasicXorShift64(result_type seed) noexcept;

    MC_NODISCARD static constexpr auto min() noexcept -> result_type;
    MC_NODISCARD static constexpr auto max() noexcept -> result_type;

    constexpr auto seed(result_type value = default_seed) noexcept -> void;
    constexpr auto discard(unsigned long long z) noexcept -> void;

    MC_NODISCARD constexpr auto operator()() noexcept -> result_type;

    template<typename U>
    friend constexpr auto operator==(
        BasicXorShift64<U> const& lhs,
        BasicXorShift64<U> const& rhs
    ) noexcept -> bool;

    template<typename U>
    friend constexpr auto operator!=(
        BasicXorShift64<U> const& lhs,
        BasicXorShift64<U> const& rhs
    ) noexcept -> bool;

private:
    result_type _state{default_seed};
};

using XorShift64 = BasicXorShift64<std::uint64_t>;

}  // namespace mc

#include "xorshift64.impl.hpp"
