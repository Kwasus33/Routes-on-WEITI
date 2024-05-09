#include "program_manager.hpp"

int main(int argc, char *argv[])
{
    ProgramManager program(800, 600);

    while(program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}