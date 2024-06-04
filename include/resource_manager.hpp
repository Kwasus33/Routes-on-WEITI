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
    void LoadTextureFromBitmap(const char* filePath, const int flr, SDL_Renderer* sdlRenderer);
    const std::map<int,Floor>& GetFloors() const { return floors; }
    const Floor& GetFloor(int floor) const { return floors.at(floor); }
    const Path& GetPath() const { return path; }
    void SetPathFromGraph(Graph* graph, const std::vector<int>& nodePath) 
        {path.SetFromGraph(graph, nodePath);}
};