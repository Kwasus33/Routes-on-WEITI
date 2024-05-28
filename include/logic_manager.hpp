#pragma once

#include "graph.hpp"

class LogicManager
{
    const static int MAX_FLOOR = 1;
    const static int MIN_FLOOR = -1;
    int currentFloor;
    Graph graph;
public:
    LogicManager();
    void UpdatePath();
    void ChangeFloor(int change);
};