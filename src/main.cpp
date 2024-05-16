#include "program_manager.hpp"
#include <SDL.h>
#include <iostream>
#include "file_handle.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
    // std::vector<std::string> arguments;

    // for (int i = 1; i < argc; ++i) {
    //     std::string arg(argv[i]);

    //     if (arg == "-h" || arg == "--help") {
    //         std::cout << "Usage: " << argv[0] << " [options]\n";
    //         std::cout << "Options:\n";
    //         std::cout << "  -h, --help  Show this help message\n";
    //     }
    //     else if (arg == "-f" || arg == "--find") {
    //         // call findRoute() func
    //     }
    //     else if (arg == "-" || arg == "--find"){
    //         arguments.push_back(arg);
    //     }
    // }

    // // Process custom arguments
    // for (const std::string& arg : arguments) {
    //     // Add your custom argument processing logic here
    //     std::cout << "Custom argument: " << arg << "\n";
    // }

    jsonReader fh("../test/test.json");
    Graph gr = fh.addNodes();

    ProgramManager program(800, 600, &gr);

    program.InitFloors();
    try
    {
        program.UpdatePath("0", "82");
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