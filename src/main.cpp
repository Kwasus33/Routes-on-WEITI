#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>
#include <list>
#include "file_handler.hpp"
#include "graph.hpp"

std::list<std::string> parseArguments(int argc, char *argv[])
{
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
    return {id_1, id_2};
}

int main(int argc, char *argv[])
{
    std::unique_ptr<FileReader> fh = std::make_unique<jsonReader>("../test/test.json");
    Graph gr = fh->ReadDataIntoGraph();

    std::list<std::string> args = parseArguments(argc, argv);

    ProgramManager program(800, 600, &gr);

    try
    {
        program.UpdatePath(args.front(), args.back());
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
    program.InitFloors();
    while (program.IsRunning())
    {
        program.ProcessInput();
        program.Update();
        program.Render();
    }

    return 0;
}