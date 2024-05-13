#pragma once

#include "SDL.h"
#include <vector>
#include "point.h"

struct Floor
{
    SDL_Texture* texture;
    std::vector<Point> path;
    SDL_Rect transform;

    Floor() = default;
    Floor(SDL_Texture* texture, const SDL_Rect& transform)
        : texture{texture}, transform{transform} {}
};