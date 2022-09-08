#pragma once

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

    [[nodiscard]] static constexpr auto min() noexcept -> result_type;
    [[nodiscard]] static constexpr auto max() noexcept -> result_type;

    constexpr auto seed(result_type value = default_seed) noexcept -> void;
    constexpr auto discard(unsigned long long z) noexcept -> void;

    [[nodiscard]] constexpr auto operator()() noexcept -> result_type;

    friend constexpr auto
    operator==(BasicXorShift32 const& lhs, BasicXorShift32 const& rhs) noexcept
        -> bool;
    friend constexpr auto
    operator!=(BasicXorShift32 const& lhs, BasicXorShift32 const& rhs) noexcept
        -> bool;

private:
    result_type _state{default_seed};
};

using XorShift32 = BasicXorShift32<std::uint32_t>;

}  // namespace mc

#include "xorshift32.impl.hpp"
