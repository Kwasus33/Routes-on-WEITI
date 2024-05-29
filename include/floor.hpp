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
    void SetTransfrom(const SDL_Rect& t) 
        { transform = t; }
    
    SDL_Texture* GetTexture() const { return texture; }
    SDL_Rect GetTransfrom() const { return transform; }
};