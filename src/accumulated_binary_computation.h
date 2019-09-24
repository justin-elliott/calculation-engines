// accumulated_binary_computation.h
// A templated class providing a concrete implementation of a Computation that maintains a simple
// accumulator value over binary operations.

#ifndef ACCUMULATED_BINARY_COMPUTATION_H
#define ACCUMULATED_BINARY_COMPUTATION_H

#include <numeric>
#include <optional>

#include "computation.h"

template <typename BinaryOperation>
class AccumulatedBinaryComputation : public Computation
{
public:
    AccumulatedBinaryComputation() = default;

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
// Implementations based upon AccumulatedBinaryComputations

using MultiplierComputation = AccumulatedBinaryComputation<std::multiplies<Integer>>;
using DividerComputation = AccumulatedBinaryComputation<std::divides<Integer>>;

#endif // ACCUMULATED_BINARY_COMPUTATION_H
