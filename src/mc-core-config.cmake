# SPDX-License-Identifier: BSL-1.0

include(CMakeFindDependencyMacro)

if(NOT EMSCRIPTEN)
    find_dependency(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
endif()

find_dependency(concurrentqueue REQUIRED)
find_dependency(fmt REQUIRED)
find_dependency(gcem REQUIRED)
find_dependency(readerwriterqueue REQUIRED)
find_dependency(Threads REQUIRED)
find_dependency(xsimd REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/mc-core-targets.cmake")
