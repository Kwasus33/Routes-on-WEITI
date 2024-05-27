#pragma once

#include "program_manager.hpp"
#include "map"
#include "SDL.h"
#include "commands.hpp"

class Command;
class ProgramManager;

enum class InputType
{
    QUIT
};

class InputManager
{
    std::map<InputType, Command*> commandMap;
    SDL_Event event;

public:
    InputManager(ProgramManager* programManager);
    ~InputManager();
    void Update();
};