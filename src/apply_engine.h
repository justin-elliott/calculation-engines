// apply_engine.h
// Apply an engine to a stream of integer values.

#ifndef APPLY_ENGINE_H
#define APPLY_ENGINE_H

#include <optional>
#include <string>
#include <iosfwd>

#include "computation.h"

// Apply the engine to a single input stream.
std::optional<std::string> applyEngine(Computation& engine, std::istream& stream);

// Apply the engine to a list of files, delimited by iterators.
std::optional<std::string> applyEngine(Computation& engine, char** filesBegin, char** filesEnd);

#endif // APPLY_ENGINE_H
