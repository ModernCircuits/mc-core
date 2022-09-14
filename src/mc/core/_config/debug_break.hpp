
// SPDX-License-Identifier: BSD-2-Clause
// Copied from https://github.com/scottt/debugbreak
// (5dcbe41d2bd4712c8014aa7e843723ad7b40fd74) 2022-09-14

/* Copyright (c) 2011-2021, Scott Tsai
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

// NOLINTBEGIN

#ifdef _MSC_VER

#define mcDebugBreak __debugbreak

#else

#define DEBUG_BREAK_USE_TRAP_INSTRUCTION 1
#define DEBUG_BREAK_USE_BULTIN_TRAP      2
#define DEBUG_BREAK_USE_SIGTRAP          3

#if defined(__i386__) || defined(__x86_64__)

#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION

inline void trap_instruction() { __asm__ volatile("int $0x03"); }

#elif defined(__arm__) && !defined(__thumb__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION

inline void trap_instruction() { __asm__ volatile(".inst 0xe7f001f0"); }
#elif defined(__aarch64__) && defined(__APPLE__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_BULTIN_DEBUGTRAP
#elif defined(__aarch64__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION

inline void trap_instruction() { __asm__ volatile(".inst 0xd4200000"); }
#else
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_SIGTRAP
#endif

#ifndef DEBUG_BREAK_IMPL
#error "debugbreak.h is not supported on this target"
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_TRAP_INSTRUCTION
inline void mcDebugBreak() { trap_instruction(); }
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_BULTIN_DEBUGTRAP
inline void mcDebugBreak() { __builtin_debugtrap(); }
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_BULTIN_TRAP
inline void mcDebugBreak() { __builtin_trap(); }
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_SIGTRAP
#include <signal.h>

inline void mcDebugBreak() { raise(SIGTRAP); }
#else
#error "invalid DEBUG_BREAK_IMPL value"
#endif

#endif

// NOLINTEND
