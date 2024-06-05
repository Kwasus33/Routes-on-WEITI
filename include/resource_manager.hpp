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
    void loadTextureFromBitmap(const char* filePath, const int flr, SDL_Renderer* sdlRenderer);
    const std::map<int,Floor>& getFloors() const;
    const Floor& getFloor(int floor) const;
    const Path& getPath() const;
    void setPathFromGraph(Graph* graph, const std::vector<int>& nodePath);
};