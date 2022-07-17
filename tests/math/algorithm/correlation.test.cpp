#include "mc/math.hpp"

#include "mc/array.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace math = mc::math;

TEMPLATE_TEST_CASE("math/algorithm: correlation", "[math][algorithm]", float, double, long double)
{
    using T = TestType;

    auto x = std::array<T, 5> { 15, 18, 21, 24, 27 };
    auto y = std::array<T, 5> { 25, 25, 27, 31, 32 };
    REQUIRE(math::correlation(begin(x), end(x), begin(y), end(y)) == Catch::Approx(T(0.953463)));
}
