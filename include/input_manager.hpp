#pragma once

#include "program_manager.hpp"
#include "map"
#include "SDL.h"

enum class InputType
{
    QUIT
};

class InputManager
{
    std::map<InputType, Command*> commandMap;
    SDL_Event event;

public:
    InputManager(const ProgramManager& programManager);
    ~InputManager();
    void Update();
};