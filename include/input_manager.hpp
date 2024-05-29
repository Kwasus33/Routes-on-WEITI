#pragma once

#include "program_manager.hpp"
#include "map"
#include "SDL.h"
#include "commands.hpp"

class Command;
class ProgramManager;

enum class InputType
{
    QUIT,
    FLOOR_UP, FLOOR_DOWN
};

class InputManager
{
    std::map<InputType, Command*> commandMap;
    SDL_Event event;

public:
    InputManager(ProgramManager* programManager, LogicManager* LogicManager);
    ~InputManager();
    void Update();
};