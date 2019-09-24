// computation.h
// An abstract class representing a single step of an engine computation. A function-object style is
// followed for interoperability with standard algorithms.
//
// Usage:
//   TypeDerivedFromComputation computation;
//   computation(value1);
//   computation(value2);
//   ...
//   computation(valueN);
//   Integer result = computation.value();

#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "non_copyable.h"
#include "integer.h"

class Computation : private NonCopyable
{
public:
    virtual ~Computation() = default;

    // Update the state of the computation to include value
    virtual void operator()(Integer value) = 0;

    // Retrieve the final value of the computation
    virtual Integer value() = 0;
};

#endif // COMPUTATION_H
