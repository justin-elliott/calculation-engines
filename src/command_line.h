// command_line.h
// Parse and classify a command line.

#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>
#include "input_type.h"

// Parsed representation of the command line.
struct CommandLine
{
    std::string program;
    std::string engineName;
    InputType inputType;
    const char** inputBegin;
    const char** inputEnd;
};

// Parse the command line arguments as passed to main().
CommandLine parseCommandLine(int argc, char* argv[]);

#endif // COMMAND_LINE_H
