#pragma once

#include "SDL.h"
#include "floor.h"
#include <map>

class ProgramManager
{
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning = true;
    std::map<int, Floor> floors;
    int viewedFloor = 0;
    const int MAX_FLOOR = 0;
    const int MIN_FLOOR = -1;
public:
    ProgramManager(int screenWidth, int screenHeight);
    ~ProgramManager();
    
    void Init();
    void ProcessInput();
    void Update();
    void Render();
    bool IsRunning();
};