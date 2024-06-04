#include "program_manager.hpp"
#include <iostream>
#include "argParser.hpp"


int main(int argc, char *argv[])
{
    argParser argParser(argc, argv);
    ParserState state = argParser.parseArguments(argc, argv);
    ProgramManager programManager;

    switch (state)
    {
    case ParserState::TUI:
        {
            std::list<std::string> args = argParser.parseTUI();

            if (argParser.getState() == TuiCommand::FIND_PATH)
            {
                //programManager.setGraph(args.front(), args.back());
                programManager.Run();
            }

            else if (argParser.getState() == TuiCommand::FIND_CLASSROOM)
            {
                //programManager.findClassroom(args.front());
                programManager.Run();
            }
        }
        break;

    case ParserState::GUI:
        programManager.Run();
        break;

    default:
        break;
    }

    return 0;
}