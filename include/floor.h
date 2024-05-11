#pragma once

#include "SDL.h"
#include <vector>
#include "Point.h"

struct Floor
{
    SDL_Texture* texture;
    std::vector<Point> path;
    SDL_Rect transform;
};