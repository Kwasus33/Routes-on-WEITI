#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class Graph
{
    public:
    void addNode(Node new_node);
    std::vector<Node>& getNodes();
    private:
    std::vector<Node> nodes;
    std::vector<bool> hasRoutes;
};