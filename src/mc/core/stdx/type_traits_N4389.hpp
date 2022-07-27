// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <type_traits>

namespace mc {
template<bool B>
using BoolConstant = std::integral_constant<bool, B>;
using TrueType     = BoolConstant<true>;
using FalseType    = BoolConstant<false>;
}  // namespace mc
