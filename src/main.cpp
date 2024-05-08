#include "program_manager.hpp"

int main(int argc, char *argv[])
{
    ProgramManager program(200, 200);

    while(program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}