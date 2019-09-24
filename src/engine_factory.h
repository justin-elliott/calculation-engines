// engine_factory.h
// A class allowing the registration and retrieval of calculation engines.
//
// Usage:
//   EngineFactory engineFactory;
//   engineFactory.registerEngine<MyComputation>("my_computation", InputType::Integers);
//   auto myEngine = engineFactory.make("my_computation", InputType::Integers);

#ifndef ENGINE_FACTORY_H
#define ENGINE_FACTORY_H

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "computation.h"
#include "non_copyable.h"

// Allowable input types allowed on the command line: files, integers, or either.
enum class InputType
{
    Files       = 0x01,
    Integers    = 0x02,
    Any         = Files | Integers
};

// -------------------------------------------------------------------------------------------------

class EngineFactory : private NonCopyable
{
private:
    using ComputationFactory = std::function<std::unique_ptr<Computation> ()>;
    using EngineDetails = std::tuple<InputType, ComputationFactory>;

public:
    // Register a computation function with the given name and accepted input types.
    template <typename Computation>
    void registerEngine(const std::string& engineName, InputType inputType = InputType::Any);

    // Create an engine computation. If no matching engine name or input type is found, nullptr
    // is returned.
    std::unique_ptr<Computation> make(const std::string& engineName, InputType inputType);

    // Retrieve the names of all of the registered engines.
    std::vector<std::string> registeredEngines() const;

private:
    std::map<std::string, EngineDetails> engines;
};

// -------------------------------------------------------------------------------------------------

template <typename Computation>
inline void EngineFactory::registerEngine(const std::string& engineName, InputType inputType)
{
    ComputationFactory computationFactory = []() -> std::unique_ptr<Computation> {
        return std::make_unique<Computation>();
    };
    engines.insert({ engineName, std::make_tuple(inputType, computationFactory) });
}

#endif // ENGINE_FACTORY_H
