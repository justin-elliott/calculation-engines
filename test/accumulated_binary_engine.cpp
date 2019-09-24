// test/accumulated_binary_engine.cpp
// Tests for the accumulated binary engine.

#include "catch.hpp"
#include "src/accumulated_binary_engine.h"

TEST_CASE("Can implement a new AccumulatedBinaryEngine", "[AccumulatedBinaryEngine]") {
    AccumulatedBinaryEngine<std::plus<Integer>> addition;

    addition(1);
    addition(2);
    addition(3);

    REQUIRE(addition.value() == 6);
}

TEST_CASE("Can perform division with the build in DividerEngine", "[AccumulatedBinaryEngine]") {
    DividerEngine divider;

    // calculate 60 / 5 / 4
    divider(60);
    divider(5);
    divider(4);

    REQUIRE(divider.value() == 3);
}
