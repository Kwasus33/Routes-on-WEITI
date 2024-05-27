#include "program_manager.hpp"
#include <iostream>
#include "file_handler.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
    // std::vector<std::string> arguments;
    // std::string id_1;
    // std::string id_2;

    // for (int i = 1; i < argc; ++i) {
    //     std::string arg(argv[i]);
    //     try {
    //         if (i == 1 && (arg == "-h" || arg == "--help")) {
    //             std::cout << "Usage: " << argv[0] << std::endl;
    //             std::cout << "main.cpp [classroom1_number] [classroom2_number]";
    //             return 0;
    //         }
    //         else {
    //             if (i == 1)
    //                 id_1 = arg;
    //             else if (i == 2)
    //                 id_2 = arg;
    //             else
    //                 continue;
    //         }
    //     }
    //     catch(const std::exception& e) {
    //         std::cerr << e.what() << '\n';
    //     }
    // }
    // std::unique_ptr<FileReader> fh = std::make_unique<jsonReader>("../test/test.json");
    // Graph gr = fh->ReadDataIntoGraph();

    // ProgramManager program(800, 600, &gr);


    // try
    // {
    //     program.UpdatePath(id_1, id_2);
    // }
    // catch (std::invalid_argument &e)
    // {
    //     std::cout << e.what() << '\n';
    //     return 1;
    // }
    // program.InitFloors();
    // while (program.IsRunning())
    // {
    //     program.ProcessInput();
    //     program.Update();
    //     program.Render();
    // }

    // return 0;

    ProgramManager programManager;
    programManager.Run();
    return 0;
}