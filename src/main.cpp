#include "program_manager.hpp"
#include <iostream>
#include "argParser.hpp"


int main(int argc, char *argv[])
{
    argParser argParser(argc, argv);
    argParser.parseArguments(argc, argv);

    // ProgramManager programManager;
    // programManager.Run();
    return 0;
}