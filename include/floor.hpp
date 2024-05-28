#pragma once

#include "SDL.h"

class Floor
{
    SDL_Texture* texture;
    SDL_Rect transfrom;
public:
    Floor() = default;
    Floor(SDL_Texture* texture)
        : texture(texture) {}
    ~Floor()
        { SDL_DestroyTexture(texture); }
};