project(tests)

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(mc-core-tests)
catch_discover_tests(mc-core-tests)

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

        "math/algorithm/correlation.test.cpp"
        "math/algorithm/crossProduct.test.cpp"
        "math/algorithm/dotProduct.test.cpp"
        "math/algorithm/linearSolve.test.cpp"
        "math/algorithm/normalized.test.cpp"
        "math/algorithm/normalize.test.cpp"

        "math/dense/DynamicVector.test.cpp"
        "math/dense/DynamicMatrix.test.cpp"

        "units/Duration.cpp"
        "units/FrameCount.cpp"
        "units/Frequency.cpp"

        "stdx/bit.cpp"
        "stdx/format.cpp"
        "stdx/iterator.cpp"
        "stdx/numbers.cpp"
        "stdx/numeric.cpp"
)
