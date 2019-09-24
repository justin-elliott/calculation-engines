// apply_engine.h
// Apply an engine to a stream of integer values.

#ifndef APPLY_ENGINE_H
#define APPLY_ENGINE_H

#include <optional>
#include <string>
#include <iosfwd>

#include "engine.h"

// Apply the engine to a single input stream.
// On error, a string describing the problem is returned.
std::optional<std::string> applyEngine(Engine& engine, std::istream& stream);

// Apply the engine to a list of files, delimited by iterators.
// On error, a string describing the problem is returned.
std::optional<std::string> applyEngine(Engine& engine, const char** filesBegin, const char** filesEnd);

#endif // APPLY_ENGINE_H
