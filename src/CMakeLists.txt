cmake_minimum_required(VERSION 3.15)
project(mc-core VERSION 0.1.0)

find_package(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
find_package(fmt REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)
find_package(xsimd REQUIRED)

add_library(mc-core INTERFACE)
add_library(mc::core ALIAS mc-core)
set_target_properties(mc-core PROPERTIES EXPORT_NAME core)

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

# installation
include(GNUInstallDirs)
install(TARGETS mc-core EXPORT mc-coreTargets)
install(DIRECTORY mc TYPE INCLUDE)

# local build
export(EXPORT mc-coreTargets NAMESPACE mc::)
configure_file("mc-coreConfig.cmake" "." COPYONLY)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(mc-coreConfigVersion.cmake COMPATIBILITY SameMajorVersion)

# installation
install(
    EXPORT 
        mc-coreTargets 
    DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/core 
    NAMESPACE 
        mc::
)

install(
    FILES 
        mc-coreConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/mc-coreConfigVersion.cmake
    DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/core
)