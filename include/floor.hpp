#pragma once

#include "SDL.h"

class Floor
{
    SDL_Texture* texture;
    SDL_Rect transform;
public:
    Floor() = default;
    Floor(SDL_Texture* texture, const SDL_Rect& transform)
        : texture(texture), transform(transform) {}
    
    const SDL_Texture* GetTexture() const { return texture; }
    const SDL_Rect GetTransfrom() const { return transform; }
};