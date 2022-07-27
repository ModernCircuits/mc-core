# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.21)
project(mc-core VERSION 0.2.0 LANGUAGES CXX)

find_package(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
find_package(fmt REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)
find_package(xsimd REQUIRED)

add_library(mc-core INTERFACE)
add_library(mc::core ALIAS mc-core)

set_target_properties(mc-core PROPERTIES
    CXX_VISIBILITY_PRESET
        hidden
    VISIBILITY_INLINES_HIDDEN
        YES
    VERSION
        "${PROJECT_VERSION}"
    SOVERSION
        "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME
        core
)

target_include_directories(mc-core
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


target_link_libraries(mc-core
    INTERFACE
        Boost::headers
        Boost::container
        Boost::filesystem
        concurrentqueue::concurrentqueue
        fmt::fmt
        readerwriterqueue::readerwriterqueue
        xsimd
)

install(
    TARGETS
        "mc-core"
    EXPORT
        "mc-core-targets"
    LIBRARY DESTINATION
        "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION
        "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION
        "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION
        "${CMAKE_INSTALL_INCLUDEDIR}"
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    mc-core-config-version.cmake
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)

configure_file(mc-core-config.cmake.in mc-core-config.cmake @ONLY)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/mc-core-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/mc-core-config-version.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
    EXPORT
        mc-core-targets
    NAMESPACE
        mc::
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)