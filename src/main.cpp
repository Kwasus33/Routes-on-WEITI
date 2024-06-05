#include "console_interface.hpp"
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
                programManager.run(Action::SHOW_PATH, args.front(), args.back());
            }

            else if (argParser.getState() == TuiCommand::FIND_CLASSROOM)
            {
                programManager.run(Action::SHOW_DESCRIPTION, args.front());
            }

            else if (argParser.getState() == TuiCommand::QUIT)
            {
                return 0;
            }
        }
        break;

    case ParserState::GUI:
        programManager.run();
        break;

    default:
        break;
    }

    return 0;
}