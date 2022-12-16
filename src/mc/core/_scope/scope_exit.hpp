// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

namespace mc {

template<typename Callback>
struct ScopeExit
{
    explicit ScopeExit(Callback&& callback)
        : _callback{static_cast<Callback&&>(callback)}
    {}

    ~ScopeExit()
    {
        if (_active) { _callback(); }
    }

    auto release() -> void { _active = false; }

private:
    Callback _callback;
    bool _active{true};
};

namespace detail {

enum struct ScopeExitFactory
{
};

template<typename Func>
auto operator+(ScopeExitFactory /*unused*/, Func&& func) -> ScopeExit<Func>
{
    return ScopeExit<Func>(static_cast<Func&&>(func));
}

}  // namespace detail

}  // namespace mc

#define SCOPE_EXIT                                                             \
    auto MC_ANONYMOUS_VAR(SCOPE_EXIT_STATE)                                    \
        = ::mc::detail::ScopeExitFactory{} + [&]()  // NOLINT
