#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>
#include "file_handle.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
    std::vector<std::string> arguments;
    std::string id_1;
    std::string id_2;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        try {
            if (i == 1 && (arg == "-h" || arg == "--help")) {
                std::cout << "Usage: " << argv[0] << std::endl;
                std::cout << "main.cpp [classroom1_number] [classroom2_number]";
            }
            else {
                if (i == 1)
                    id_1 = arg;
                else if (i == 2)
                    id_2 = arg;
                else
                    continue;
            }
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    jsonReader fh("../test/test.json");
    Graph gr = fh.addNodes();

    ProgramManager program(800, 600, &gr);

    program.InitFloors();
    try
    {
        program.UpdatePath(id_1, id_2);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }

    while (program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}