#pragma once

#include "SDL.h"

class Floor
{
    SDL_Texture* texture;
    SDL_Rect transfrom;
public:
    Floor(SDL_Texture* texture)
        : texture(texture) {}
};