#include "mc/dsp/Frequency.hpp"

#include <catch2/catch.hpp>

namespace dsp = mc::dsp;

TEMPLATE_TEST_CASE(
    "stl/dsp: Frequency", "[stl][dsp]", float, double, long double)
{
    using T         = TestType;
    using Hertz     = dsp::Frequency<T, std::ratio<1>>;
    using Kilohertz = dsp::Frequency<T, std::ratio<1'000>>;
    using Bpm       = dsp::Frequency<T, std::ratio<1, 60>>;

    using HertzInt     = dsp::Frequency<int, std::ratio<1>>;
    using KilohertzInt = dsp::Frequency<int, std::ratio<1'000>>;

    REQUIRE(Hertz(1).count() == T(1));
    REQUIRE(Kilohertz(1).count() == T(1));
    REQUIRE((+Hertz(1)).count() == T(+1));
    REQUIRE((-Hertz(1)).count() == T(-1));

    REQUIRE(Hertz { Kilohertz(1) }.count() == T(1'000));
    REQUIRE(Bpm { Hertz(1) }.count() == T(60));

    auto a = Hertz(T(1));
    a += Hertz(T(1));
    REQUIRE(a.count() == T(2));
    a -= Hertz(T(1));
    REQUIRE(a.count() == T(1));
    a *= T(4);
    REQUIRE(a.count() == T(4));
    a /= T(2);
    REQUIRE(a.count() == T(2));

    using dsp::frequencyCast;
    REQUIRE(frequencyCast<Hertz>(Hertz { T(1) }).count() == T(1));
    REQUIRE(frequencyCast<Hertz>(Kilohertz { T(1) }).count() == T(1'000));
    REQUIRE(frequencyCast<Kilohertz>(Hertz { T(1'000) }).count() == T(1));
    REQUIRE(frequencyCast<Bpm>(Hertz { T(1) }).count() == T(60));
    REQUIRE(frequencyCast<Hertz>(Bpm { T(120) }).count() == T(2));
    REQUIRE(frequencyCast<Kilohertz>(Bpm { T(120'000) }).count() == T(2));

    REQUIRE(frequencyCast<HertzInt>(Hertz { T(1) }).count() == 1);
    REQUIRE(frequencyCast<HertzInt>(Kilohertz { T(1) }).count() == 1'000);
    REQUIRE(frequencyCast<KilohertzInt>(HertzInt { 1 }).count() == 0);

    // REQUIRE((dsp::Hertz(1) - dsp::Hertz(1)).count() == T(0));
    // REQUIRE((dsp::Hertz(1) * 2).count() == T(2));
}