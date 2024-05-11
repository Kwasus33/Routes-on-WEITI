#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class Graph
{
    public:
    void addNode(Node new_node);
    std::vector<Node>& getNodes();
    void findRoutes(int nodeID);
    std::vector<int> getRoute(int start, int end);
    private:
    std::vector<Node> nodes;
    std::vector<bool> hasRoutes;
    void changeRoute(int start, int end, int which, int distance);
};