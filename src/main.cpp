#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>
#include "file_handle.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
    jsonReader fh("../test/test.json");
    Graph gr = fh.addNodes();

    std::string str1 = "01";
    std::string str2 = "52";

    int class1 = gr.findClassroom(str1);
    int class2 = gr.findClassroom(str2);

    gr.findRoutes(class1);
    std::vector<int> result = gr.getRoute(class1, class2);
    
    for (int i : result)
    {
        std::cout << i << " ";
    }
    
    std::cout << std::endl;
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