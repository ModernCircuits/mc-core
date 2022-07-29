project(tests)

find_package(Catch2 REQUIRED)
# include(Catch)

add_executable(mc-core-tests)
add_test(NAME mc-core-tests COMMAND mc-core-tests)
# catch_discover_tests(mc-core-tests)

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
        "all_headers.cpp"

        "container/ThreadSafeQueue.cpp"

        "units/Duration.cpp"
        "units/FrameCount.cpp"

        "stdx/bit.cpp"
        "stdx/format.cpp"
        "stdx/iterator.cpp"
        "stdx/numbers.cpp"
        "stdx/numeric.cpp"
)
