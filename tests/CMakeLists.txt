project(mc_stl_tests)

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(${PROJECT_NAME})
catch_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        mc::mc_stl
        Catch2::Catch2WithMain 
        mc::compiler_options
        mc::compiler_warnings
        mc::coverage
)

target_sources(${PROJECT_NAME}
    PRIVATE
        all_headers.cpp
        stdx/bit_test.cpp
)