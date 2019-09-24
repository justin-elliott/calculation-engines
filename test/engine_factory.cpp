// test/engine_factory.cpp
// Tests for the EngineFactory.

#include <sstream>

#include "catch.hpp"
#include "src/accumulated_binary_engine.h"
#include "src/engine_factory.h"

TEST_CASE("Can instantiate a factory", "[EngineFactory]") {
    EngineFactory factory;

    REQUIRE(factory.registeredEngines().empty());
}

TEST_CASE("Can register an engine", "[EngineFactory]") {
    EngineFactory factory;

    factory.registerEngine<DividerEngine>("divider", InputType::Integers);
    
    auto registered = factory.registeredEngines();

    REQUIRE(!registered.empty());
    REQUIRE(std::count(registered.begin(), registered.end(), "divider") == 1);
}

TEST_CASE("Can make an engine", "[EngineFactory]") {
    EngineFactory factory;

    factory.registerEngine<DividerEngine>("divider", InputType::Integers);
    
    auto engine = factory.make("divider", InputType::Integers);

    REQUIRE(engine);
}

TEST_CASE("Handles unknown engines", "[EngineFactory]") {
    EngineFactory factory;

    factory.registerEngine<DividerEngine>("divider", InputType::Integers);
    
    auto engine = factory.make("multiplier", InputType::Integers);

    REQUIRE(!engine);
}

TEST_CASE("Handles unsupported input types", "[EngineFactory]") {
    EngineFactory factory;

    factory.registerEngine<DividerEngine>("divider", InputType::Integers);
    
    auto engine = factory.make("divider", InputType::None);

    REQUIRE(!engine);
}
