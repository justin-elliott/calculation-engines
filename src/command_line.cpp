// command_line.cpp
// Parse and classify a command line.

#include <algorithm>
#include <regex>

#include "command_line.h"

CommandLine parseCommandLine(int argc, char* argv[]) {
    if (argc < 3) {
        // invalid input: too few arguments
        return { argv[0], std::string(), InputType::None, nullptr, nullptr };
    }

    const char** inputBegin = const_cast<const char**>(argv + 2);
    const char** inputEnd = const_cast<const char**>(argv + argc);

    // Determine if the input range is all numeric.
    std::regex digitRegEx("\\d+");
    auto digitMatch = [&digitRegEx](const char* s) -> bool {
        return std::regex_match(s, digitRegEx);
    };
    bool isNumeric = std::all_of(inputBegin, inputEnd, digitMatch);

    return {
        argv[0],
        argv[1],
        isNumeric ? InputType::Integers : InputType::Files,
        inputBegin,
        inputEnd
    };
}
