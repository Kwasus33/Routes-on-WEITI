#pragma once

#include "SDL.h"


class GraphicsManager
{
private:
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
public:
    GraphicsManager(int screenWidth, int screenHeight);
    ~GraphicsManager();
};