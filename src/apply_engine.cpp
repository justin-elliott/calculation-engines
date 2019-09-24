// apply_engine.cpp
// Apply an engine to a stream of integer values.

#include <fstream>

#include "apply_engine.h"

std::optional<std::string> applyEngine(Engine& engine, std::istream& stream) {
    std::for_each(
        std::istream_iterator<Integer>(stream),
        std::istream_iterator<Integer>(),
        std::ref(engine));
    return stream.eof() ? std::nullopt : std::make_optional("Invalid integer on stream");
}

std::optional<std::string> applyEngine(Engine& engine, char** filesBegin, char** filesEnd) {
    for (char** files = filesBegin; files != filesEnd; ++files) {
        std::string filename(*files);
        filename += ".txt";

        std::ifstream stream(filename);
        if (!stream) {
            return "Unable to open file \"" + filename + '"';
        }
        if (auto result = applyEngine(engine, stream)) {
            return result;
        }
    }
    return std::nullopt;
}
