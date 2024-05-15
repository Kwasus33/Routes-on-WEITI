#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>
#include "file_handle.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
    jsonReader fh("../test/eiti.json");
    Graph gr = fh.addNodes(fh.LoadFromFile());
    for (Node node : gr.getNodes())
    {
        std::cout << node.getClassrooms()[0].getName();
    }
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