#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "graph.hpp"

class MapPath
{
    std::map<int,std::vector<SDL_Point>> pointsByFloor;
public:
    MapPath();
    void setFromGraph(Graph* graph, const std::vector<int>& nodePath);
    const std::vector<SDL_Point>& getPointsOnFloor(const int floor) const;
};