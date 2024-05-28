#pragma once

#include "SDL.h"

class Renderer
{
    int windowWidth, windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Renderer(int windowWidth, int windoHeight);
    void Render();
    SDL_Renderer* GetSdlRenderer() const { return renderer; }
};