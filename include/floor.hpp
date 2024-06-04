#pragma once

#include "SDL.h"
#include <memory>

struct SDLTextureDeleter 
{
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

class Floor
{
    std::unique_ptr<SDL_Texture,SDLTextureDeleter> texture;
    SDL_Rect transform;
public:
    Floor() = default;
    Floor(SDL_Texture* texture, const SDL_Rect& transform)
        : texture(texture), transform(transform) {}
    
    SDL_Texture* GetTexture() const { return texture.get(); }
    const SDL_Rect GetTransfrom() const { return transform; }
};