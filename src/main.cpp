#include "program_manager.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "start" << std::endl;
    ProgramManager program(800, 600);

    while(program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}