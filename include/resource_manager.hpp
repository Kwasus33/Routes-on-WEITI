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
    ResourceManager();
    SDL_Texture* LoadTextureFromBitmap(std::string filePath);
};