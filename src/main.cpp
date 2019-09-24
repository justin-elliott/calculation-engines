// main.cpp

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>

#include "accumulated_binary_engine.h"
#include "apply_engine.h"
#include "command_line.h"
#include "engine_factory.h"

void usage(const CommandLine& commandLine, const EngineFactory& engineFactory)
{
    std::cerr << "Usage:" << std::endl
        << "  " << commandLine.program << " engine_name files..." << std::endl
        << "  " << commandLine.program << " engine_name integers..." << std::endl
        << std::endl
        << "Available engines:" << std::endl << "  ";
    auto registeredEngines = engineFactory.registeredEngines();
    std::copy(registeredEngines.begin(), registeredEngines.end(),
        std::ostream_iterator<std::string>(std::cerr, " "));
    std::cerr << std::endl;
}

int main(int argc, char* argv[])
{
    EngineFactory engineFactory;
    engineFactory.registerEngine<MultiplierEngine>("multiplier", InputType::Files);
    engineFactory.registerEngine<DividerEngine>("divider", InputType::Any);

    CommandLine commandLine = parseCommandLine(argc, argv);
    if (commandLine.inputType == InputType::None) {
        std::cerr << "Invalid arguments" << std::endl;
        usage(commandLine, engineFactory);
        return EXIT_FAILURE;
    }

    auto engine = engineFactory.make(commandLine.engineName, commandLine.inputType);
    if (!engine) {
        std::cerr << "Unknown engine \"" << commandLine.engineName
            << "\", or unavailable input type" << std::endl;
        usage(commandLine, engineFactory);
        return EXIT_FAILURE;
    }
    
    std::optional<std::string> error;

    if (commandLine.inputType == InputType::Integers) {
        // Create a stream directly from the input arguments.
        std::stringstream stream;
        std::copy(argv + 2, argv + argc, std::ostream_iterator<std::string>(stream, " "));

        error = applyEngine(*engine, stream);
    } else {
        error = applyEngine(*engine, commandLine.inputBegin, commandLine.inputEnd);
    }

    if (error) {
        std::cerr << *error << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << engine->value() << std::endl;

    return EXIT_SUCCESS;
}
