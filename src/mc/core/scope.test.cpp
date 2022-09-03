// SPDX-License-Identifier: BSL-1.0

#include <mc/core/scope.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("scope.hpp: ScopeExit", "[scope]")
{
    auto counter = 0;
    REQUIRE(counter == 0);
    {
        SCOPE_EXIT { ++counter; };
    }

    REQUIRE(counter == 1);
    {
        SCOPE_EXIT { ++counter; };
        SCOPE_EXIT { ++counter; };
    }
    REQUIRE(counter == 3);
}

TEST_CASE("scope.hpp: ScopeFail", "[scope]")
{
    auto counter = 0;
    REQUIRE(counter == 0);
    {
        SCOPE_FAIL { ++counter; };
    }

    REQUIRE(counter == 0);
    {
        SCOPE_FAIL { ++counter; };
        SCOPE_FAIL { ++counter; };
    }
    REQUIRE(counter == 0);

    try {
        SCOPE_FAIL { ++counter; };
        SCOPE_FAIL { ++counter; };
        throw 42;
    } catch (int) {
        REQUIRE(counter == 2);
    }
}
