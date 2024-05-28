#pragma once

#include "floor.hpp"
#include "path.hpp"
#include <map>
#include <string>
#include "SDL.h"

class ResourceManager
{
    std::map<int,Floor> floors;
    Path path;
public:
    ResourceManager(SDL_Renderer* sdlRenderer);
    SDL_Texture* LoadTextureFromBitmap(const char* filePath, SDL_Renderer* sdlRenderer);
};