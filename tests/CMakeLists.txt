project(mc_stl_tests)

add_executable(${PROJECT_NAME})
catch_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        mc::mc_stl
        mc::compiler_options
        mc::compiler_warnings
        mc::coverage
        Catch2::Catch2WithMain
)

target_sources(${PROJECT_NAME}
    PRIVATE
        all_headers.cpp
        container/ThreadSafeQueue.cpp
        stdx/bit.cpp
        stdx/format.cpp
        stdx/numbers.cpp
        stdx/numeric.cpp
)

