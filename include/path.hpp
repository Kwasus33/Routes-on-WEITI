#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "graph.hpp"

class Path
{
    std::map<int,std::vector<SDL_Point>> pointsByFloor;
public:
    Path() = default;
    void SetFromGraph(Graph graph);
};