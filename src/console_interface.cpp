#include "console_interface.hpp"

ConsoleInterface::ConsoleInterface(const LogicManager* logicManager)
    : logicManager(logicManager) {}

Action ConsoleInterface::GetNextAction() const
{
    while (true)
    {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "p: Show me a path between two classrooms." << std::endl;
        std::cout << "d: Show me the description of a classroom." << std::endl;
        std::cout << "q: Quit." << std::endl << std::endl;

        std::string input;
        std::cin >> input;

        if (input == "p"){
            return Action::SHOW_PATH;
        }
        else if (input == "d"){
            return Action::SHOW_DESCRIPTION;
        }
        else if (input == "q"){
            return Action::QUIT;
        }
        
        std::cout << "Invalid input. Try again." << std::endl << std::endl;
    }
}