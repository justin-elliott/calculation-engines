// main.cpp

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>

#include "accumulated_binary_computation.h"
#include "engine_factory.h"

void usage(const char* program, const EngineFactory& engineFactory)
{
    std::cerr << "Usage:" << std::endl
        << "  " << program << " engine_name files..." << std::endl
        << "  " << program << " engine_name integers..." << std::endl
        << std::endl
        << "Available engines:" << std::endl << "  ";
    auto registeredEngines = engineFactory.registeredEngines();
    std::copy(registeredEngines.begin(), registeredEngines.end(),
        std::ostream_iterator<std::string>(std::cerr, " "));
    std::cerr << std::endl;
}

int main(int argc, char** argv)
{
    const char* program = argv[0];
    
    EngineFactory engineFactory;
    engineFactory.registerEngine<MultiplierComputation>("multiplier", InputType::Files);
    engineFactory.registerEngine<DividerComputation>("divider", InputType::Any);

    if (argc < 3) {
        usage(program, engineFactory);
        return EXIT_FAILURE;
    }

    const std::string engineName = argv[1];

    std::stringstream args;
    std::copy(argv + 2, argv + argc, std::ostream_iterator<std::string>(args, " "));

    auto engine = engineFactory.make(engineName, InputType::Files);
    if (!engine) {
        usage(program, engineFactory);
        return EXIT_FAILURE;
    }
    
    std::for_each(
        std::istream_iterator<Integer>(args),
        std::istream_iterator<Integer>(),
        std::ref(*engine));
    std::cout << engine->value() << std::endl;

    return EXIT_SUCCESS;
}
