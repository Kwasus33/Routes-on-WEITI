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
    const std::map<int,Floor>& getFloors() const { return floors; }
    const Floor& getFloor(int floor) const { return floors.at(floor); }
    const Path& getPath() const { return path; }
    void setPathFromGraph(Graph* graph, const std::vector<int>& nodePath) 
        {path.setFromGraph(graph, nodePath);}
};