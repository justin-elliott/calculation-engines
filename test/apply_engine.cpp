// test/apply_engine.cpp
// Tests for applyEngine functions.

#include <sstream>

#include "catch.hpp"
#include "src/apply_engine.h"
#include "src/accumulated_binary_engine.h"

TEST_CASE("Can apply a divider engine to a stream", "[applyEngine]") {
    DividerEngine divider;
    std::stringstream stream("60 5 4");

    auto error = applyEngine(divider, stream);

    REQUIRE(!error);
    REQUIRE(divider.value() == 3);
}

TEST_CASE("Handles invalid integers on a stream", "[applyEngine]") {
    DividerEngine divider;
    std::stringstream stream("60 5 4 xx 1");

    auto error = applyEngine(divider, stream);

    REQUIRE(error);
}

TEST_CASE("Can apply a divider engine to a list of files", "[applyEngine]") {
    DividerEngine divider;
    const char* files[] = { "test/sequence", "test/one" };

    auto error = applyEngine(divider, std::begin(files), std::end(files));

    REQUIRE(!error);
    REQUIRE(divider.value() == 5);
}

TEST_CASE("Handles missing files", "[applyEngine]") {
    DividerEngine divider;
    const char* files[] = { "test/no_file" };

    auto error = applyEngine(divider, std::begin(files), std::end(files));

    REQUIRE(error);
}

TEST_CASE("Handles files containing invalid integers", "[applyEngine]") {
    DividerEngine divider;
    const char* files[] = { "test/invalid" };

    auto error = applyEngine(divider, std::begin(files), std::end(files));

    REQUIRE(error);
}
