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
    void setFromGraph(Graph* graph, const std::vector<int>& nodePath);
    const std::vector<SDL_Point>& getPointsOnFloor(const int floor) const;
};