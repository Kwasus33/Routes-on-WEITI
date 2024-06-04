#include "program_manager.hpp"
#include <iostream>
#include "argParser.hpp"


int main(int argc, char *argv[])
{
    argParser argParser(argc, argv);
    // auto rooms = parseArguments(argc, argv);
    ProgramManager programManager;
    // programManager.setgraph(rooms[0], rooms[1]);
    programManager.Run();
    return 0;
}