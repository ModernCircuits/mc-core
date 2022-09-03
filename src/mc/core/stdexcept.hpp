// SPDX-License-Identifier: BSL-1.0
#pragma once

#include <stdexcept>

namespace mc {
using LogicError      = std::logic_error;
using DomainError     = std::domain_error;
using InvalidArgument = std::invalid_argument;
using LengthError     = std::length_error;
using OutOfRange      = std::out_of_range;
using RuntimeError    = std::runtime_error;
using OverflowError   = std::overflow_error;
using UnderflowError  = std::underflow_error;
using RangeError      = std::range_error;
}  // namespace mc
