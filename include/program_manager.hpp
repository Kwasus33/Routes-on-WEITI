#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <map>

class ProgramManager
{
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    std::map<int, SDL_Texture*> floors;
public:
    ProgramManager(int screenWidth, int screenHeight);
    ~ProgramManager();
    
    void ProcessInput();
    void Update();
    void Render();
    bool IsRunning();
};