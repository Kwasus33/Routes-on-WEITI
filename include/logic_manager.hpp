#pragma once

#include "graph.hpp"
#include "resource_manager.hpp"
#include <string>

class LogicManager
{
    int currentFloor;
    Graph graph;
    ResourceManager* resourceManager;
public:
    LogicManager(ResourceManager* resourceManager);
    void UpdatePath(std::string& start, std::string& end);
    void ChangeFloor(const int change);
    int GetCurrentFloor() { return currentFloor; }
};