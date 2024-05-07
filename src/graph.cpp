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
        Node& currentNode = nodes[start];
        int nextNodeID = currentNode.getNextNodes()[end];
        currentNode.addRoute(which, distance, nextNodeID);
        distance -= currentNode.getDistances()[nextNodeID];
        start = nextNodeID;
    }
}

void Graph::findRoutes(int nodeID)
{
    // checks if graph has node of this ID
    if (nodeID >= nodes.size())
    {
        throw std::invalid_argument("Index out of range");
        return;
    }

    // Creates priority queue and reference to starting node
    Node& startingNode = nodes[nodeID];
    std::deque<int> nodesQueue;
    nodesQueue.push_back(nodeID);
    // creates container to mark Nodes as visited
    std::vector<bool> visited;
    while (visited.size() < nodes.size())
        visited.push_back(false);

    // Main loop with responisbility of walking through the whole graph
    while (!nodesQueue.empty())
    {
        // prioritize the queue basing on actual distance from source
        std::sort(nodesQueue.begin(), nodesQueue.end(), [&startingNode](int nodeOne, int nodeTwo)
                  {std::vector<int> distances = startingNode.getDistances(); return distances[nodeOne] < distances[nodeTwo]; });

        std::vector<int> originDistances = startingNode.getDistances();

        Node &currentNode = nodes[nodesQueue.front()];
        nodesQueue.pop_front();

        // walk through all the routes available from this graph
        for (int node = 0; node < currentNode.getDistances().size(); ++node)
        {
            if (node == currentNode.getNextNodes()[node] && node != currentNode.getID())
            {
                if (!visited[node])
                    nodesQueue.push_back(node);

                int new_distance = originDistances[currentNode.getID()] + currentNode.getDistances()[node];

                if (originDistances[node] > new_distance)
                    this->changeRoute(nodeID, currentNode.getID(), node, new_distance);
            }
        }
        visited[currentNode.getID()] = true;
    }
    hasRoutes[nodeID] = true;
}

std::vector<Node> &Graph::getNodes()
{
    return nodes;
}