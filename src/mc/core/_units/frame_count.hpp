// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/cstdint.hpp>

namespace mc {

/// \ingroup group-units
struct FrameCount
{
    constexpr FrameCount() noexcept = default;
    constexpr FrameCount(std::uint64_t initialCount) noexcept;

    MC_NODISCARD constexpr auto count() const noexcept -> std::uint64_t;
    MC_NODISCARD constexpr operator std::uint64_t() const noexcept;

private:
    std::uint64_t _count{0};
};

constexpr auto operator+=(FrameCount& fc, std::uint64_t countToAdd) noexcept
    -> FrameCount&;

template<typename T>
constexpr auto operator+=(FrameCount& fc, T countToAdd) noexcept -> FrameCount&;

// impl
constexpr FrameCount::FrameCount(std::uint64_t initialCount) noexcept
    : _count{initialCount}
{}

constexpr auto FrameCount::count() const noexcept -> std::uint64_t
{
    return _count;
}

constexpr FrameCount::operator std::uint64_t() const noexcept { return _count; }

constexpr auto operator+=(FrameCount& fc, std::uint64_t countToAdd) noexcept
    -> FrameCount&
{
    fc = FrameCount{fc.count() + countToAdd};
    return fc;
}

template<typename T>
constexpr auto operator+=(FrameCount& fc, T countToAdd) noexcept -> FrameCount&
{
    return fc += static_cast<std::uint64_t>(countToAdd);
}

}  // namespace mc
