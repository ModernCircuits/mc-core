cmake_minimum_required(VERSION 3.15)
project(mc_stl VERSION 0.1.0)

find_package(Boost 1.78 REQUIRED COMPONENTS container filesystem json)
find_package(fmt REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)

find_package(Catch2 REQUIRED)
set_target_properties(Catch2::Catch2 PROPERTIES IMPORTED_GLOBAL TRUE)
set_target_properties(Catch2::Catch2WithMain PROPERTIES IMPORTED_GLOBAL TRUE)
include(Catch)

add_library(mc_stl INTERFACE)
add_library(mc::mc_stl ALIAS mc_stl)
set_target_properties(mc_stl PROPERTIES EXPORT_NAME stl)

target_include_directories(mc_stl
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


target_link_libraries(mc_stl
    INTERFACE
        Boost::headers
        Boost::container
        Boost::filesystem
        concurrentqueue::concurrentqueue
        fmt::fmt
        readerwriterqueue::readerwriterqueue
)

include(GNUInstallDirs)
install(TARGETS mc_stl EXPORT mcstlTargets)
install(EXPORT mcstlTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake NAMESPACE mc::)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/mc DESTINATION include)