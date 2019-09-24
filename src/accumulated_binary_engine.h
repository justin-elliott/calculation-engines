// accumulated_binary_engine.h
// A templated class providing a concrete implementation of a Engine that maintains a simple
// accumulator value over binary operations.

#ifndef ACCUMULATED_BINARY_ENGINE_H
#define ACCUMULATED_BINARY_ENGINE_H

#include <numeric>
#include <optional>

#include "engine.h"

template <typename BinaryOperation>
class AccumulatedBinaryEngine : public Engine
{
public:
    AccumulatedBinaryEngine() = default;

    virtual void operator()(Integer value) override {
        if (accumulator.has_value()) {
            accumulator = binaryOperation(*accumulator, value);
        } else {
            accumulator = value;
        }
    }

    virtual Integer value() override {
        return accumulator.value_or(0);
    }

private:
    BinaryOperation binaryOperation;
    std::optional<Integer> accumulator;
};

// -------------------------------------------------------------------------------------------------
// Implementations based upon AccumulatedBinaryEngines

using MultiplierEngine = AccumulatedBinaryEngine<std::multiplies<Integer>>;
using DividerEngine = AccumulatedBinaryEngine<std::divides<Integer>>;

#endif // ACCUMULATED_BINARY_ENGINE_H
