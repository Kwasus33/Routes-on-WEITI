#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "graph.hpp"

class Path
{
    std::map<int,std::vector<SDL_Point>> pointsByFloor;
public:
    Path();
    void SetFromGraph(const Graph& graph, const std::vector<int>& nodePath);
};