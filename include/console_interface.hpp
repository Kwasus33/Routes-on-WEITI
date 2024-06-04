#pragma once

#include "graph.hpp"
#include "input_manager.hpp"

enum class Action
{
    NONE, QUIT, SHOW_PATH, SHOW_DESCRIPTION
};

class ConsoleInterface
{
    LogicManager* logicManager;

public:
    ConsoleInterface(LogicManager* logicManager);

    Action GetNextAction() const;
    void SetNewPath() const;
    void ShowDescription() const;
};