# SPDX-License-Identifier: BSL-1.0

include(CMakeFindDependencyMacro)

find_dependency(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
find_dependency(fmt REQUIRED)
find_dependency(concurrentqueue REQUIRED)
find_dependency(readerwriterqueue REQUIRED)
find_dependency(xsimd REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/mc-core-targets.cmake")