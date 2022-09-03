# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.21)
project(mc-core-dev LANGUAGES CXX)

option(MC_CORE_ENABLE_COVERAGE    "Build with coverage enabled"                       OFF)
option(MC_CORE_ENABLE_ASAN        "Build with address sanitizer enabled"              OFF)
option(MC_CORE_ENABLE_UBSAN       "Build with undefined behavior sanitizer enabled"   OFF)
option(MC_CORE_ENABLE_TSAN        "Build with thread sanitizer enabled"               OFF)
option(MC_CORE_ENABLE_MSAN        "Build with memory sanitizer enabled"               OFF)
option(MC_CORE_ENABLE_WERROR      "Build with warnings as errors"                     OFF)

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

        "src/mc/core/bit.test.cpp"
        "src/mc/core/format.test.cpp"
        "src/mc/core/iterator.test.cpp"
        "src/mc/core/numbers.test.cpp"
        "src/mc/core/numeric.test.cpp"
        "src/mc/core/queue.test.cpp"
        "src/mc/core/scope.test.cpp"
        "src/mc/core/units.test.cpp"
)
