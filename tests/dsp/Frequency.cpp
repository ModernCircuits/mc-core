#include "mc/dsp/Frequency.hpp"

#include <catch2/catch.hpp>

namespace dsp = mc::dsp;

TEMPLATE_TEST_CASE("stl/dsp: Frequency", "[stl][dsp]", int, long)
{
    using T = TestType;

    REQUIRE(dsp::Hertz(1).count() == T(1));
    REQUIRE(dsp::Kilohertz(1).count() == T(1));
    REQUIRE((+dsp::Hertz(1)).count() == T(+1));
    REQUIRE((-dsp::Hertz(1)).count() == T(-1));

    REQUIRE(dsp::Hertz { dsp::Kilohertz(1) }.count() == T(1'000));
    REQUIRE(dsp::Bpm { dsp::Hertz(1) }.count() == T(60));

    auto a = dsp::Hertz(1);
    a += dsp::Hertz(1);
    REQUIRE(a.count() == T(2));
    a -= dsp::Hertz(1);
    REQUIRE(a.count() == T(1));
    a *= 4.0f;
    REQUIRE(a.count() == 4.0f);
    a /= 2.0f;
    REQUIRE(a.count() == 2.0f);

    // REQUIRE((dsp::Hertz(1) - dsp::Hertz(1)).count() == T(0));
    // REQUIRE((dsp::Hertz(1) * 2).count() == T(2));

    using Hertzf  = dsp::Frequency<float>;
    auto const hf = Hertzf { 1 };
    REQUIRE(hf.count() == 1.0f);
}