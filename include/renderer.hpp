#pragma once

#include "SDL.h"


class Renderer
{
private:
    int screenWidth, screenHeight;
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    
public:
    Renderer(int screenWidth, int screenHeight);
    ~Renderer();
};