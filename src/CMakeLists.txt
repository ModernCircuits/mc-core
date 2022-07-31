# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.21)
project(mc-core VERSION 0.3.3 LANGUAGES CXX)

if(NOT EMSCRIPTEN)
    find_package(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
endif()

find_package(fmt REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)
find_package(Threads REQUIRED)
find_package(xsimd REQUIRED)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(mc-core INTERFACE)
add_library(mc::core ALIAS mc-core)

set_target_properties(mc-core PROPERTIES
    CXX_VISIBILITY_PRESET
        hidden
    VISIBILITY_INLINES_HIDDEN
        YES
    VERSION
        ${PROJECT_VERSION}
    SOVERSION
        ${PROJECT_VERSION_MAJOR}
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
        $<$<NOT:$<BOOL:${EMSCRIPTEN}>>:Boost::headers>
        $<$<NOT:$<BOOL:${EMSCRIPTEN}>>:Boost::container>
        $<$<NOT:$<BOOL:${EMSCRIPTEN}>>:Boost::filesystem>
        
        concurrentqueue::concurrentqueue
        fmt::fmt
        readerwriterqueue::readerwriterqueue
        Threads::Threads
        xsimd
)

if(EMSCRIPTEN)
    set_target_properties(mc-core PROPERTIES 
        COMPILE_FLAGS 
            "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0" 
        LINK_FLAGS 
            "-s USE_BOOST_HEADERS=1 -s DISABLE_EXCEPTION_CATCHING=0"
    )
endif()

install(
    TARGETS
        mc-core
    EXPORT
        mc-core-targets
)

export(
    EXPORT
        mc-core-targets
    NAMESPACE
        mc::
)

configure_file("mc-core-config.cmake" "." COPYONLY)
write_basic_package_version_file(mc-core-config-version.cmake COMPATIBILITY SameMajorVersion)

install(
    EXPORT
        mc-core-targets
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/mc-core
    NAMESPACE
        mc::
)

install(
    FILES
        mc-core-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/mc-core-config-version.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/mc-core
)
