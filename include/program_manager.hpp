#pragma once

#include "SDL.h"
#include "floor.h"
#include <map>

class ProgramManager
{
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    std::map<int, Floor> floors;
public:
    ProgramManager(int screenWidth, int screenHeight);
    ~ProgramManager();
    
    void Init();
    void ProcessInput();
    void Update();
    void Render();
    bool IsRunning();
};