#pragma once

#include "graph.hpp"

class LogicManager
{
    int currentFloor;
    Graph graph;
public:
    LogicManager();
    void UpdatePath();
    void ChangeFloor(int change);
};