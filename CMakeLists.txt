cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(modern-circuits-lib-stl VERSION 0.1.0)

option(MC_BUILD_COVERAGE   "Build with coverage enabled"                       OFF)
option(MC_BUILD_ASAN       "Build with address sanitizer enabled"              OFF)
option(MC_BUILD_UBSAN      "Build with undefined behavior sanitizer enabled"   OFF)
option(MC_BUILD_TSAN       "Build with thread sanitizer enabled"               OFF)
option(MC_BUILD_MSAN       "Build with memory sanitizer enabled"               OFF)
option(MC_BUILD_WERROR     "Build with warnings as errors"                     OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    find_program(CCACHE ccache)
    if (CCACHE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    endif ()

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(BUILD_SHARED_LIBS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    enable_testing()
    include(CTest)
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
include(mcConan)
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

find_package(Boost 1.77 REQUIRED COMPONENTS container filesystem json)
find_package(fmt REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)
find_package(tcb-span REQUIRED)
find_package(Catch2 REQUIRED)
set_target_properties(Catch2::Catch2 PROPERTIES IMPORTED_GLOBAL TRUE)
set_target_properties(Catch2::Catch2WithMain PROPERTIES IMPORTED_GLOBAL TRUE)
include(Catch)


add_library(mc_stl INTERFACE)
add_library(mc::mc_stl ALIAS mc_stl)
target_include_directories(mc_stl INTERFACE ${PROJECT_SOURCE_DIR})
target_link_libraries(mc_stl
    INTERFACE
        Boost::headers
        Boost::container
        Boost::filesystem
        Boost::json
        fmt::fmt
        Microsoft.GSL::Microsoft.GSL
        concurrentqueue::concurrentqueue
        readerwriterqueue::readerwriterqueue
        tcb-span::tcb-span
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()
