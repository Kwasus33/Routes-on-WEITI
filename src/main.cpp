#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "start" << std::endl;
    ProgramManager program(800, 600);

    program.Init();

    while(program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}