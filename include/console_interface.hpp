#pragma once

#include "graph.hpp"
#include "input_manager.hpp"
#include "user_action.hpp"

class ConsoleInterface
{
    LogicManager* logicManager;

public:
    ConsoleInterface(LogicManager* logicManager);

    Action GetNextAction() const;
    void SetNewPath(std::string room1 = "", std::string room2 = "") const;
    void ShowDescription(std::string room1 = "") const;
};