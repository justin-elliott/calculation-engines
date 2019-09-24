// engine_factory.cpp
// A class allowing the registration and retrieval of calculation engines.

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "engine_factory.h"

std::unique_ptr<Computation> EngineFactory::make(const std::string& engineName, InputType inputType) {
    auto engineDetails = engines.find(engineName);
    if (engineDetails == engines.end()) {
        return nullptr;
    }
    auto [acceptedTypes, computationFactory] = engineDetails->second;
    if ((inputType & acceptedTypes) == InputType::None) {
        return nullptr;
    }
    return computationFactory();
}

std::vector<std::string> EngineFactory::registeredEngines() const {
    std::vector<std::string> result;
    std::for_each(
        engines.begin(),
        engines.end(),
        [&result](const auto& entry) { result.push_back(entry.first); });
    return result;
}
