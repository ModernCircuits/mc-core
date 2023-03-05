# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.21)
project(mc-core-dev LANGUAGES CXX)

option(MODERNCIRCUITS_ENABLE_COVERAGE    "Build with coverage enabled"                       OFF)
option(MODERNCIRCUITS_ENABLE_ASAN        "Build with address sanitizer enabled"              OFF)
option(MODERNCIRCUITS_ENABLE_UBSAN       "Build with undefined behavior sanitizer enabled"   OFF)
option(MODERNCIRCUITS_ENABLE_TSAN        "Build with thread sanitizer enabled"               OFF)
option(MODERNCIRCUITS_ENABLE_MSAN        "Build with memory sanitizer enabled"               OFF)
option(MODERNCIRCUITS_ENABLE_WERROR      "Build with warnings as errors"                     OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
include(CTest)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake)
include(compiler_options)
include(compiler_warnings)
include(code_coverage)

add_subdirectory(src)

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(mc-core-tests)
catch_discover_tests(mc-core-tests)

target_link_libraries(mc-core-tests
    PRIVATE
        mc::core
        mc::compiler_options
        mc::compiler_warnings
        mc::coverage
        Catch2::Catch2WithMain
)

target_sources(mc-core-tests
    PRIVATE
        "src/mc/core.test.cpp"

        "src/mc/core/_bit/byteswap.test.cpp"
        "src/mc/core/_bit/bit.test.cpp"
        "src/mc/core/_cmath/cmath.test.cpp"
        "src/mc/core/_exception/raise.test.cpp"
        "src/mc/core/_expected/expected.test.cpp"
        "src/mc/core/_format/format.test.cpp"
        "src/mc/core/_iterator/iterator.test.cpp"
        "src/mc/core/_numbers/numbers.test.cpp"
        "src/mc/core/_numeric/numeric.test.cpp"
        "src/mc/core/_random/xorshift32.test.cpp"
        "src/mc/core/_random/xorshift64.test.cpp"
        "src/mc/core/_ranges/ranges.test.cpp"
        "src/mc/core/_queue/thread_safe_queue.test.cpp"
        "src/mc/core/_scope/scope_exit.test.cpp"
        "src/mc/core/_scope/scope_fail.test.cpp"
        "src/mc/core/_units/duration.test.cpp"
        "src/mc/core/_utility/integer_comparison_functions.test.cpp"
)
