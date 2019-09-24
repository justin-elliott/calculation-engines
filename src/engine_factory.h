// engine_factory.h
// A class allowing the registration and retrieval of calculation engines.
//
// Usage:
//   EngineFactory engineFactory;
//   engineFactory.registerEngine<MyEngine>("my_engine", InputType::Integers);
//   auto myEngine = engineFactory.make("my_engine", InputType::Integers);

#ifndef ENGINE_FACTORY_H
#define ENGINE_FACTORY_H

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "engine.h"
#include "input_type.h"
#include "non_copyable.h"

class EngineFactory : private NonCopyable
{
private:
    using EngineConstructor = std::function<std::unique_ptr<Engine> ()>;
    using EngineDetails = std::tuple<InputType, EngineConstructor>;

public:
    // Register a engine function with the given name and accepted input types.
    // Names must be unique; non-unique entries are ignored.
    template <typename Engine>
    void registerEngine(const std::string& engineName, InputType acceptedTypes = InputType::Any);

    // Create an engine engine. If no matching engine name or input type is found, nullptr
    // is returned.
    std::unique_ptr<Engine> make(const std::string& engineName, InputType inputType);

    // Retrieve the names of all of the registered engines.
    std::vector<std::string> registeredEngines() const;

private:
    std::map<std::string, EngineDetails> engines;
};

// -------------------------------------------------------------------------------------------------

template <typename Engine>
inline void EngineFactory::registerEngine(const std::string& engineName, InputType acceptedTypes)
{
    EngineConstructor constructor = []() -> std::unique_ptr<Engine> {
        return std::make_unique<Engine>();
    };
    engines.insert({ engineName, std::make_tuple(acceptedTypes, constructor) });
}

#endif // ENGINE_FACTORY_H
