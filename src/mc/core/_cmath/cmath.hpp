// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <mc/core/config.hpp>

#include <cmath>
#include <gcem.hpp>

#define MC_MAKE_CMATH_FUNC_ARGS1(func)                                         \
    MC_NODISCARD constexpr auto func(float arg)->float                         \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(arg); }                            \
        return std::func(arg);                                                 \
    }                                                                          \
    MC_NODISCARD constexpr auto func(double arg)->double                       \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(arg); }                            \
        return std::func(arg);                                                 \
    }

#define MC_MAKE_CMATH_FUNC_ARGS2(func)                                         \
    MC_NODISCARD constexpr auto func(float x, float y)->float                  \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(x, y); }                           \
        return std::func(x, y);                                                \
    }                                                                          \
    MC_NODISCARD constexpr auto func(double x, double y)->double               \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(x, y); }                           \
        return std::func(x, y);                                                \
    }

#define MC_MAKE_CMATH_FUNC_ARGS3(func)                                         \
    MC_NODISCARD constexpr auto func(float x, float y, float z)->float         \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(x, y, z); }                        \
        return std::func(x, y, z);                                             \
    }                                                                          \
    MC_NODISCARD constexpr auto func(double x, double y)->double               \
    {                                                                          \
        MC_IF_CONSTEVAL { return gcem::func(x, y, z); }                        \
        return std::func(x, y, z);                                             \
    }

namespace mc {
MC_MAKE_CMATH_FUNC_ARGS1(exp)
// MC_MAKE_CMATH_FUNC_ARGS1(exp2)
MC_MAKE_CMATH_FUNC_ARGS1(log)
MC_MAKE_CMATH_FUNC_ARGS1(log2)
MC_MAKE_CMATH_FUNC_ARGS1(log10)
MC_MAKE_CMATH_FUNC_ARGS1(sqrt)
// MC_MAKE_CMATH_FUNC_ARGS1(cqrt)
MC_MAKE_CMATH_FUNC_ARGS1(sin)
MC_MAKE_CMATH_FUNC_ARGS1(cos)
MC_MAKE_CMATH_FUNC_ARGS1(tan)
MC_MAKE_CMATH_FUNC_ARGS1(asin)
MC_MAKE_CMATH_FUNC_ARGS1(acos)
MC_MAKE_CMATH_FUNC_ARGS1(atan)

MC_MAKE_CMATH_FUNC_ARGS2(atan2)
MC_MAKE_CMATH_FUNC_ARGS2(fmod)
// MC_MAKE_CMATH_FUNC_ARGS2(remainder)
// MC_MAKE_CMATH_FUNC_ARGS2(fmax)
// MC_MAKE_CMATH_FUNC_ARGS2(fmin)
// MC_MAKE_CMATH_FUNC_ARGS2(fdim)
MC_MAKE_CMATH_FUNC_ARGS2(pow)

// MC_MAKE_CMATH_FUNC_ARGS3(fma)
}  // namespace mc
