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
    void SetTransfrom(const SDL_Rect& t) 
        { transfrom = t; }
    
    SDL_Texture* GetTexture() const { return texture; }
    SDL_Rect GetTransfrom() const { return transfrom; }
};