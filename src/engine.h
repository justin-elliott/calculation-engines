// engine.h
// An abstract class representing a single step of a stateful computation engine. A function-object
// style is followed for interoperability with standard algorithms.
//
// All engines must derive from this class, implementing the operator() to update the state of the
// engine, and value() to return the final state.
//
// Usage:
//   TypeDerivedFromEngine engine;
//   engine(value1);
//   engine(value2);
//   ...
//   engine(valueN);
//   Integer result = engine.value();

#ifndef ENGINE_H
#define ENGINE_H

#include "non_copyable.h"
#include "integer.h"

class Engine : private NonCopyable
{
public:
    virtual ~Engine() = default;

    // Update the state of the engine to include value
    virtual void operator()(Integer value) = 0;

    // Retrieve the final value of the engine
    virtual Integer value() = 0;
};

#endif // ENGINE_H
