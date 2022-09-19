// SPDX-License-Identifier: BSL-1.0

#include <mc/core/exception.hpp>
#include <mc/core/stdexcept.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

TEST_CASE("exception.hpp: raise", "[exception]", )
{
    auto foo = [] { mc::raise<mc::InvalidArgument>("foo"); };
    REQUIRE_THROWS(foo());
    REQUIRE_THROWS_AS(foo(), mc::InvalidArgument);
    REQUIRE_THROWS_WITH(foo(), "foo");
}

TEST_CASE("exception.hpp: raisef", "[exception]", )
{
    auto fooBar = [] { mc::raisef<mc::InvalidArgument>("foo {}", "bar"); };
    REQUIRE_THROWS(fooBar());
    REQUIRE_THROWS_AS(fooBar(), mc::InvalidArgument);
    REQUIRE_THROWS_WITH(fooBar(), "foo bar");
}
