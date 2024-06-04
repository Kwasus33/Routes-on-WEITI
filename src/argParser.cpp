#include "argParser.hpp"
#include <vector>
#include <iostream>



argParser::argParser(int argc, char *argv[]): argc(argc), argv(argv), state(ParserState::BEGIN) {}


std::vector<std::string> argParser::parseArguments(int argc, char *argv[])
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

    return std::vector<std::string> {id_1, id_2};
}