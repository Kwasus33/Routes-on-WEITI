#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <iostream>

void Graph::addNode(Node new_node)
{
    int nodesQunatity = nodes.size() + 1;
    if (new_node.getDistances().size() < nodesQunatity)
    {
        new_node.setDistance(nodesQunatity, __INT_MAX__);
    }
    nodes.push_back(new_node);

    for (int i = 0; i < nodesQunatity; ++i)
    {
        Node& currentNode = nodes[i];
        Node& newlyInsertedNode = nodes [nodesQunatity - 1];
        if (currentNode.getDistances().size() < nodesQunatity)
        {
            currentNode.setDistance(nodesQunatity, __INT_MAX__);
        }

        if (new_node.getNextNodes()[i] == i)
        {
            currentNode.addRoute(new_node.getID(), new_node.getDistances()[i], new_node.getID());
        }

        if  (currentNode.getNextNodes()[new_node.getID()] == new_node.getID())
        {
            newlyInsertedNode.addRoute(i, currentNode.getDistances()[new_node.getID()], i);
        }

    }
    
}

std::vector<Node>& Graph::getNodes()
{
    return nodes;
}