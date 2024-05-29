#pragma once

#include "floor.hpp"
#include "path.hpp"
#include <map>
#include <string>
#include "SDL.h"
#include "renderer.hpp"

class Renderer;

class ResourceManager
{
    std::map<int,Floor> floors;
    Path path;
public:
    ResourceManager(Renderer* renderer);
    SDL_Texture* LoadTextureFromBitmap(const char* filePath, SDL_Renderer* sdlRenderer);
    std::map<int,Floor> GetFloors() const { return floors; }
    Floor GetFloor(int floor) const { return floors.at(floor); }
    Path GetPath() const { return path; }
};