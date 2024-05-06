#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <iostream>

void Graph::addNode(Node new_node)
{
    int nodesQunatity = nodes.size() + 1;
    // adds other nodes description to node that is being added
    if (new_node.getDistances().size() < nodesQunatity)
    {
        new_node.setDistance(nodesQunatity, __INT_MAX__);
    }
    nodes.push_back(new_node);
    hasRoutes.push_back(false);

    for (int i = 0; i < nodesQunatity; ++i)
    {
        if (hasRoutes[i]) hasRoutes[i] = false;
    }

    for (int i = 0; i < nodesQunatity; ++i)
    {
        Node& currentNode = nodes[i];
        Node& newlyInsertedNode = nodes [nodesQunatity - 1];
        // adds placeholders for no information nodes to current node
        if (currentNode.getDistances().size() < nodesQunatity)
        {
            currentNode.setDistance(nodesQunatity, __INT_MAX__);
        }
        // checks if added node has information about route to this node
        if (new_node.getNextNodes()[i] == i)
        {
            currentNode.addRoute(new_node.getID(), new_node.getDistances()[i], new_node.getID());
        }
        // checks if current node has information about route to added noode
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