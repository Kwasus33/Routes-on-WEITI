#include "console_interface.hpp"
#include <iostream>
#include <iomanip>

ConsoleInterface::ConsoleInterface(LogicManager *logicManager)
    : logicManager(logicManager) {}

Action ConsoleInterface::getNextAction() const
{
    while (true)
    {
        std::cout << std::setw(52) << std::setfill('=') << "" << std::endl;

        std::cout << "What would you like to do?" << std::endl;
        std::cout << "-> Show a path between two classrooms - ENTER p" << std::endl;
        std::cout << "-> Show the description of a classroom - ENTER d" << std::endl;
        std::cout << "-> Quit - ENTER q" << std::endl;

        std::cout << std::setw(52) << std::setfill('=') << "" << std::endl;

        std::cout << "-> ";
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
            std::cout << std::setw(52) << std::setfill('=') << "" << std::endl;
            std::cout << "Goodbye! System shutting down." << std::endl;
            std::cout << std::setw(52) << std::setfill('=') << "" << std::endl;
            return Action::QUIT;
        }
        std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
    }
}

void ConsoleInterface::SetNewPath(std::string room1, std::string room2) const
{
    while (true)
    {
        // Optionally skip input if rooms are already decided
        if (room1 == "" || room2 == "")
        {
            std::cout << std::setw(52) << std::setfill('-') << "" << std::endl;
            std::cout << "Type in the name of the first classroom" << std::endl;
            std::cout << "-> ";
            std::getline(std::cin, room1);
            std::cout << std::setw(52) << std::setfill('-') << "" << std::endl;
            std::cout << "Type in the name of the second classroom:" << std::endl;
            std::cout << "-> ";
            std::getline(std::cin, room2);
            std::cout << std::setw(52) << std::setfill('-') << "" << std::endl;
        }

        try
        {
            logicManager->updatePath(room1, room2);
            return;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
            std::cout << "Invalid classroom(s) provided. Try again" << std::endl;
            std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
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
            std::cout << std::setw(52) << std::setfill('-') << "" << std::endl;
            std::cout << "Type in the name of the first classroom" << std::endl;
            std::cout << "-> ";
            std::getline(std::cin, room);
            std::cout << std::setw(52) << std::setfill('-') << "" << std::endl;
        }

        try
        {
            std::string desc = logicManager->getDescription(room);
            std::cout << std::setw(52) << std::setfill('*') << "" << std::endl;
            std::cout << desc << std::endl;
            std::cout << std::setw(52) << std::setfill('*') << "" << std::endl;
            return;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
            std::cout << "Invalid classroom(s) provided. Try again" << std::endl;
            std::cout << std::setw(52) << std::setfill('!') << "" << std::endl;
            room = "";
        }
    }
}