#pragma once

#include "graph.hpp"
#include "input_manager.hpp"

enum class Action
{
    QUIT, SHOW_PATH, SHOW_DESCRIPTION
};

class ConsoleInterface
{
    const InputManager* inputManager;

public:
    ConsoleInterface(const InputManager* inputManager);

    Action GetNextAction() const;
    void SetNewPath() const;
    void ShowDescription() const;
};