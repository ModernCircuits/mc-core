#pragma once

#include "mc/core/version.hpp"

#if defined(__cpp_lib_concepts)

    #include <concepts>

namespace mc {

template <typename T>
concept Integral = std::integral<T>;

template <typename T>
concept SignedIntegral = std::signed_integral<T>;

template <typename T>
concept UnsignedIntegral = std::unsigned_integral<T>;

template <typename T>
concept FloatingPoint = std::floating_point<T>;
} // namespace mc
#endif
