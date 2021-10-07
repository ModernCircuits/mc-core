#include "mc/dsp/Frequency.hpp"

#include <catch2/catch.hpp>

namespace dsp = mc::dsp;

TEMPLATE_TEST_CASE(
    "stl/dsp: Frequency<integral>", "[stl][dsp]", int, long, long long)
{
    using T         = TestType;
    using Hertz     = dsp::Frequency<T, std::ratio<1>>;
    using Kilohertz = dsp::Frequency<T, std::ratio<1'000>>;
    using Bpm       = dsp::Frequency<T, std::ratio<1, 60>>;

    REQUIRE(Hertz(1).count() == T(1));
    REQUIRE(Kilohertz(1).count() == T(1));
    REQUIRE((+Hertz(1)).count() == T(+1));
    REQUIRE((-Hertz(1)).count() == T(-1));

    REQUIRE(Hertz { Kilohertz(1) }.count() == T(1'000));
    REQUIRE(Bpm { Hertz(1) }.count() == T(60));

    REQUIRE(Hertz { T(1) } + Hertz { T(1) } == Hertz { T(2) });
    REQUIRE(Hertz { T(1) } + Hertz { T(2) } == Hertz { T(3) });
    REQUIRE(Hertz { T(1) } - Hertz { T(1) } == Hertz { T(0) });
    REQUIRE(Hertz { T(2) } * T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / Hertz { T(2) } == T(1));
    REQUIRE(T(2) * Hertz { T(2) } == Hertz { T(4) });

    REQUIRE(Hertz { T(1) } != Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } < Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } <= Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } > Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } >= Kilohertz { T(1) });
    REQUIRE(Hertz { T(1'000) } == Kilohertz { T(1) });

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

    REQUIRE(dsp::floor<Kilohertz>(Hertz { T(4'000) }) == Kilohertz { T(4) });
    REQUIRE(dsp::floor<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(4) });

    REQUIRE(dsp::ceil<Kilohertz>(Hertz { T(5'000) }) == Kilohertz { T(5) });
    REQUIRE(dsp::ceil<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(5) });
    REQUIRE(dsp::ceil<Kilohertz>(Hertz { T(4'400) }) == Kilohertz { T(5) });

    REQUIRE(dsp::round<Kilohertz>(Hertz { T(4'999) }) == Kilohertz { T(5) });
    REQUIRE(dsp::round<Kilohertz>(Hertz { T(4'500) }) == Kilohertz { T(4) });
    REQUIRE(dsp::round<Kilohertz>(Hertz { T(4'499) }) == Kilohertz { T(4) });

    REQUIRE(abs(Hertz { T(4) }) == Hertz { T(4) });
    REQUIRE(abs(Hertz { T(-4) }) == Hertz { T(4) });
}

TEMPLATE_TEST_CASE("stl/dsp: Frequency<floating_point>", "[stl][dsp]", float,
    double, long double)
{
    using T         = TestType;
    using Hertz     = dsp::Frequency<T, std::ratio<1>>;
    using Kilohertz = dsp::Frequency<T, std::ratio<1'000>>;
    using Bpm       = dsp::Frequency<T, std::ratio<1, 60>>;

    REQUIRE(Hertz(1).count() == T(1));
    REQUIRE(Kilohertz(1).count() == T(1));
    REQUIRE((+Hertz(1)).count() == T(+1));
    REQUIRE((-Hertz(1)).count() == T(-1));

    REQUIRE(Hertz { Kilohertz(1) }.count() == T(1'000));
    REQUIRE(Bpm { Hertz(1) }.count() == T(60));

    REQUIRE(Hertz { T(1) } + Hertz { T(1) } == Hertz { T(2) });
    REQUIRE(Hertz { T(1) } + Hertz { T(2) } == Hertz { T(3) });
    REQUIRE(Hertz { T(1) } - Hertz { T(1) } == Hertz { T(0) });
    REQUIRE(Hertz { T(2) } * T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / T(1) == Hertz { T(2) });
    REQUIRE(Hertz { T(2) } / Hertz { T(2) } == T(1));
    REQUIRE(T(2) * Hertz { T(2) } == Hertz { T(4) });

    REQUIRE(Hertz { T(1) } != Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } < Kilohertz { T(1) });
    REQUIRE(Hertz { T(1) } <= Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } > Kilohertz { T(1) });
    REQUIRE(Hertz { T(2'000) } >= Kilohertz { T(1) });
    REQUIRE(Hertz { T(1'000) } == Kilohertz { T(1) });

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

    REQUIRE(dsp::abs(Hertz { T(4) }) == Hertz { T(4) });
    REQUIRE(dsp::abs(Hertz { T(-4) }) == Hertz { T(4) });
}