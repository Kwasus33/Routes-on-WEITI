#include "console_interface.hpp"

ConsoleInterface::ConsoleInterface(LogicManager *logicManager)
    : logicManager(logicManager) {}

Action ConsoleInterface::getNextAction() const
{
    while (true)
    {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "p: Show a path between two classrooms." << std::endl;
        std::cout << "d: Show the description of a classroom." << std::endl;
        std::cout << "q: Quit." << std::endl
                  << std::endl;

        std::string input;
        std::getline(std::cin, input);

        if (input == "p")
        {
            return Action::SHOW_PATH;
        }
        else if (input == "d")
        {
            return Action::SHOW_DESCRIPTION;
        }
        else if (input == "q")
        {
            return Action::QUIT;
        }

        std::cout << "Invalid input. Try again." << std::endl
                  << std::endl;
    }
}

void ConsoleInterface::SetNewPath(std::string room1, std::string room2) const
{
    while (true)
    {
        // Optionally skip input if rooms are already decided
        if (room1 == "" || room2 == "")
        {
            std::cout << "Type in the name of the first classroom:" << std::endl;
            std::getline(std::cin, room1);
            std::cout << "Type in the name of the second classroom:" << std::endl;
            std::getline(std::cin, room2);
        }

        try
        {
            logicManager->updatePath(room1, room2);
            return;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid input. Try again." << std::endl
                      << std::endl;
            room1 = "";
            room2 = "";
        }
    }
}

void ConsoleInterface::ShowDescription(std::string room) const
{
    while (true)
    {
        // Optionally skip input if room is already decided
        if (room == "")
        {
            std::cout << "Type in the name of the classroom:" << std::endl;
            std::cin >> room;
        }

        try
        {
            std::string desc = logicManager->getDescription(room);
            std::cout << desc << std::endl;
            return;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid input. Try again." << std::endl
                      << std::endl;
            room = "";
        }
    }
}