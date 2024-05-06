#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <iostream>
#include <deque>
#include <algorithm>

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
        if (hasRoutes[i])
            hasRoutes[i] = false;
    }

    for (int i = 0; i < nodesQunatity; ++i)
    {
        Node &currentNode = nodes[i];
        Node &newlyInsertedNode = nodes[nodesQunatity - 1];
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
        if (currentNode.getNextNodes()[new_node.getID()] == new_node.getID())
        {
            newlyInsertedNode.addRoute(i, currentNode.getDistances()[new_node.getID()], i);
        }
    }
}

void Graph::changeRoute(int start, int end, int which, int distance)
{
    /*
    start indicates for the starting Node
    end indicates the last Node
    which indicates for which Node new route is being set
    */
    while (start != end)
    {
        Node &currentNode = nodes[start];
        int nextNodeID = currentNode.getNextNodes()[end];
        currentNode.addRoute(which, distance, nextNodeID);
        distance -= currentNode.getDistances()[nextNodeID];
        start = nextNodeID;
    }
}

void Graph::findRoutes(int nodeID)
{
    if (nodeID >= nodes.size())
        throw std::invalid_argument("Index out of range");
    Node &startingNode = this->getNodes()[nodeID];
    std::deque<int> nodesQueue;
    nodesQueue.push_back(nodeID);
    std::vector<bool> visited;
    while (visited.size() < nodes.size())
    {
        visited.push_back(false);
    }
    while (!nodesQueue.empty())
    {
        std::sort(nodesQueue.begin(), nodesQueue.end(), [&startingNode](int nodeOne, int nodeTwo)
                  { return startingNode.getDistances()[nodeOne] < startingNode.getDistances()[nodeTwo];});
            std::vector<int>
                originDistances = startingNode.getDistances();
        Node &currentNode = nodes[nodesQueue.front()];
        nodesQueue.pop_front();
        for (int i = 0; i < currentNode.getDistances().size(); ++i)
        {
            if (i == currentNode.getNextNodes()[i] && i != currentNode.getID())
            {
                if (!visited[i])
                    nodesQueue.push_back(i);

                if (originDistances[i] > originDistances[currentNode.getID()] + currentNode.getDistances()[i])
                {
                    this->changeRoute(nodeID, currentNode.getID(), i, originDistances[currentNode.getID()] + currentNode.getDistances()[i]);
                }
            }
        }
        visited[currentNode.getID()] = true;
    }
}

std::vector<Node> &Graph::getNodes()
{
    return nodes;
}