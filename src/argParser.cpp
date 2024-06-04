#include "argParser.hpp"
#include <vector>
#include <iostream>



argParser::argParser(int argc, char *argv[]): argc(argc), argv(argv), state(ParserState::BEGIN), command(TuiCommand::BEGIN) {}


ParserState argParser::parseArguments(int argc, char *argv[])
{
    if (argc == 1)
        state = ParserState::GUI;
    else
        state = ParserState::TUI;

    return state;
}

TuiCommand argParser::getState() const
{
    return command;
}

std::list<std::string> argParser::parseTUI() 
{
    std::string id_1;
    std::string id_2;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        try
        {
            if (i == 1 && (arg == "-h" || arg == "--help"))
            {
                std::cout << "Usage: " << argv[0] << std::endl;
                std::cout << "main.cpp [classroom1_number] [classroom2_number]";
                return;
            }
            
            else if (i == 1 && (arg == "-q" || arg == "--quit"))
            {
                std::cout << "Thank you for your time. Please score us 5 stars on Google Play!";
                command = TuiCommand::QUIT;
                return;
            }
            
            else if (i == 1 && (arg == "-p" || arg == "--path"))
               command = TuiCommand::FIND_PATH;
            
            else if (i == 1 && (arg == "-c" || arg == "--classroom"))
               command = TuiCommand::FIND_CLASSROOM;
            
            else if (i == 2 && command == TuiCommand::FIND_PATH)
                id_1 = arg;
            
            else if (i == 3 && command == TuiCommand::FIND_PATH)
                id_2 = arg;

            else if (i == 2 && command == TuiCommand::FIND_CLASSROOM)
                id_1 = arg;

            else
                continue;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    return {id_1, id_2};
}
