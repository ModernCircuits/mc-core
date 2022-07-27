# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.21)
project(mc-core-dev LANGUAGES CXX)

option(MC_CORE_ENABLE_COVERAGE    "Build with coverage enabled"                       OFF)
option(MC_CORE_ENABLE_ASAN        "Build with address sanitizer enabled"              OFF)
option(MC_CORE_ENABLE_UBSAN       "Build with undefined behavior sanitizer enabled"   OFF)
option(MC_CORE_ENABLE_TSAN        "Build with thread sanitizer enabled"               OFF)
option(MC_CORE_ENABLE_MSAN        "Build with memory sanitizer enabled"               OFF)
option(MC_CORE_ENABLE_WERROR      "Build with warnings as errors"                     OFF)

find_program(CCACHE ccache)
if(CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
include(CTest)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

add_subdirectory(src)
add_subdirectory(tests)
