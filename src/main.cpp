// main.cpp

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>

#include "accumulated_binary_computation.h"
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
    engineFactory.registerEngine<MultiplierComputation>("multiplier", InputType::Files);
    engineFactory.registerEngine<DividerComputation>("divider", InputType::Any);

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
    
    if (commandLine.inputType == InputType::Integers) {
        std::stringstream args;
        std::copy(argv + 2, argv + argc, std::ostream_iterator<std::string>(args, " "));

        std::for_each(
            std::istream_iterator<Integer>(args),
            std::istream_iterator<Integer>(),
            std::ref(*engine));
        std::cout << engine->value() << std::endl;
    } else {

    }

    return EXIT_SUCCESS;
}
