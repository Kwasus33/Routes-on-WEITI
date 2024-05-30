#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class Graph
{
public:
    void addNode(Node& new_node);
    std::vector<Node>& getNodes();
    void findRoutes(const int nodeID);
    std::vector<int> getRoute(int start, int end);
    std::vector<int> findClassrooms(std::string& className) const;
    int getDistance(int start, int end);
private:
    std::vector<Node> nodes;
    std::vector<bool> hasRoutes;
    void changeRoute(const int start, const int end, const int which, const int distance);
};