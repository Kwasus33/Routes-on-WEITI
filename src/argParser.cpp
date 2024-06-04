#include "argParser.hpp"
#include "program_manager.hpp"
#include <vector>
#include <iostream>



argParser::argParser(int argc, char *argv[]): argc(argc), argv(argv), state(ParserState::BEGIN) {}


void argParser::parseArguments(int argc, char *argv[])
{
    if (argc == 1)
        state = ParserState::GUI;
    else
        state = ParserState::TUI;

    switch (state)
    {
    case ParserState::TUI:
        parseTUI(argc, argv);
        break;
    case ParserState::GUI:
        parseGUI();
        break;
    default:
        break;
    }
    return;
}
    
void argParser::parseGUI()
{
    ProgramManager programManager;
    programManager.Run();
}

void argParser::parseTUI(int argc, char *argv[]) 
{
    TuiCommand command = TuiCommand::BEGIN;
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

    ProgramManager programManager;

    switch (command)
    {
    case TuiCommand::FIND_PATH:
        // programManager.setgraph(id_1, id_2);
        break;
    case TuiCommand::FIND_CLASSROOM:
        // programManager.findClassroom(id_1);
        break;
    default:
        break;
    }

}
