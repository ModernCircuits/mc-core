// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <mc/core/stdx/exception_N4152.hpp>

namespace mc {

template<typename Callback>
struct ScopeExit
{
    explicit ScopeExit(Callback&& callback)
        : callback_{static_cast<Callback&&>(callback)}
    {}

    ~ScopeExit()
    {
        if (_active) { callback_(); }
    }

    auto release() -> void { _active = false; }

private:
    Callback callback_;
    bool _active{true};
};

namespace detail {

enum struct ScopeExitFactory
{};

template<typename Func>
auto operator+(ScopeExitFactory /*unused*/, Func&& func) -> ScopeExit<Func>
{
    return ScopeExit<Func>(static_cast<Func&&>(func));
}

}  // namespace detail

}  // namespace mc

#define SCOPE_EXIT                                                             \
    auto MC_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE)                               \
        = ::mc::detail::ScopeExitFactory{} + [&]()  // NOLINT
