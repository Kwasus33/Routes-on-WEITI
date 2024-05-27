#pragma once

#include "SDL.h"

class Renderer
{
    int windowWitdth, windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Renderer(int windowWidth, int windoHeight);
    void Render();
};