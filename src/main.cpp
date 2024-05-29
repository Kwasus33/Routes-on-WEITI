#include "program_manager.hpp"
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
<<<<<<< HEAD
=======
    return {id_1, id_2};
}

int main(int argc, char *argv[])
{
    std::vector<std::string> pathsVec = {"../test/test.json", "../test/eiti.json"};
    std::unique_ptr<FileReader> fh = std::make_unique<jsonReader>(pathsVec);
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
>>>>>>> 858d5411645e967315a82c8252b52ecb53883faa

    ProgramManager programManager;
    programManager.setgraph(id_1, id_2);
    programManager.Run();
    return 0;
}