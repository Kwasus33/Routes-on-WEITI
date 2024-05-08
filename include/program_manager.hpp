#pragma once

#include "SDL.h"

class ProgramManager
{
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
public:
    ProgramManager(int screenWidth, int screenHeight);
    ~ProgramManager();
    
    void ProcessInput();
    void Update();
    void Render();
    bool IsRunning();
};