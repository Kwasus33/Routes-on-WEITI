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
    void updatePath(std::string& start, std::string& end);
    void changeFloor(const int change);
    std::string getDescription(std::string className);
    int getCurrentFloor();
};