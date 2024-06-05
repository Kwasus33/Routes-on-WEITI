#include "floor.hpp"

Floor::Floor(SDL_Texture* texture, const SDL_Rect& transform)
    : texture(texture), transform(transform) {}


SDL_Texture* Floor::GetTexture() const 
{
    return texture.get(); 
}

const SDL_Rect Floor::GetTransfrom() const 
{
    return transform;
}