#include "mc/units.hpp"

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("stl/units: toMilliseconds", "[stl][units]", int, long)
{
    using T            = TestType;
    using Seconds      = mc::Seconds<T>;
    using Milliseconds = mc::Milliseconds<T>;

    CHECK(mc::toMilliseconds(Seconds { 1 }).count() == T(1'000));
    CHECK(mc::toMilliseconds(Seconds { 2 }).count() == T(2'000));
    CHECK(mc::toMilliseconds(Milliseconds { 2 }).count() == T(2));
}

TEMPLATE_TEST_CASE("stl/units: toSeconds", "[stl][units]", int, long)
{
    using T            = TestType;
    using Seconds      = mc::Seconds<T>;
    using Milliseconds = mc::Milliseconds<T>;

    CHECK(mc::toSeconds(Seconds { 1 }).count() == T(1));
    CHECK(mc::toSeconds(Milliseconds { 1'000 }).count() == T(1));
}
