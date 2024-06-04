#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <iostream>
#include <deque>
#include <algorithm>

void addNodeInfo(std::vector<Node> &nodes, const int nodesQuantity, const int id)
{
    auto nodesQuantityCasted = static_cast<std::vector<int>::size_type>(nodesQuantity);
    Node &currentNode = nodes[id];
    Node &newlyInsertedNode = nodes[nodesQuantity - 1];
    // adds placeholders for no information nodes to current node
    if (currentNode.getDistances().size() < nodesQuantityCasted)
    {
        currentNode.setDistance(nodesQuantity - 1, std::numeric_limits<int>::max());
    }
    // checks if added node has information about route to this node
    if (newlyInsertedNode.getNextNodes()[id] == currentNode.getID())
    {
        if (currentNode.getID() == newlyInsertedNode.getID())
        {
            currentNode.setDistance(id, 0);
            currentNode.setNextNode(id, id);
        }
        else
        {

            currentNode.addRoute(newlyInsertedNode.getID(), newlyInsertedNode.getDistances()[id], newlyInsertedNode.getID());
        }
    }
    // checks if current node has information about route to added noode
    if (currentNode.getNextNodes()[newlyInsertedNode.getID()] == newlyInsertedNode.getID())
    {
        newlyInsertedNode.addRoute(currentNode.getID(), currentNode.getDistances()[newlyInsertedNode.getID()], currentNode.getID());
    }
};

void Graph::addNode(Node &new_node)
{
    int nodesQuantity = nodes.size() + 1;

    // adds other nodes description to node that is being added
    auto nodesQuantityCasted = static_cast<std::vector<int>::size_type>(nodesQuantity);
    if (new_node.getDistances().size() < nodesQuantityCasted)
    {
        // new_node.setDistance(nodesQuantity - 1, __INT_MAX__);
        new_node.setDistance(nodesQuantity - 1, std::numeric_limits<int>::max());
        new_node.addRoute(new_node.getID(), 0, new_node.getID());
    }
    nodes.push_back(new_node);
    hasRoutes.push_back(false);

    for (int i = 0; i < nodesQuantity; ++i)
    {
        if (hasRoutes[i])
        {
            hasRoutes[i] = false;
        }
    }

    for (int i = 0; i < nodesQuantity; ++i)
    {
        addNodeInfo(nodes, nodesQuantityCasted, i);
    }
}

void Graph::changeRoute(int start, int through, const int end, int distance)
{
    /*
    start indicates for the starting Node
    through indicates the last known Node
    end indicates for which Node new route is being set
    */
    while (start != through)
    {
        Node &currentNode = nodes[start];
        int nextNodeID = currentNode.getNextNodes()[through];
        currentNode.addRoute(end, distance, nextNodeID);
        distance -= currentNode.getDistances()[nextNodeID];
        start = nextNodeID;
    }
}

void Graph::findRoutes(int nodeID)
{
    // checks if graph has node of this ID
    auto nodeIDCasted = static_cast<std::vector<int>::size_type>(nodeID);
    if (nodeIDCasted >= nodes.size())
    {
        throw std::invalid_argument("Index out of range");
        return;
    }

    if (hasRoutes[nodeID])
        return;

    // Creates priority queue and reference to starting node
    Node &startingNode = nodes[nodeID];
    std::deque<int> nodesQueue;
    nodesQueue.push_back(nodeID);

    std::vector<bool> visited(nodes.size(), false);

    // Main loop with responisbility of walking through the whole graph
    while (!nodesQueue.empty())
    {
        std::vector<int> originDistances = startingNode.getDistances();
        // prioritize the queue basing on actual distance from source

        std::sort(nodesQueue.begin(), nodesQueue.end(), [&originDistances](int nodeOne, int nodeTwo)
                  { return originDistances[nodeOne] < originDistances[nodeTwo]; });

        Node &currentNode = nodes[nodesQueue.front()];
        nodesQueue.pop_front();

        // walk through all the routes available from this graph
        int currentNodeDistancesCasted = static_cast<int>(currentNode.getDistances().size());
        for (int node = 0; node < currentNodeDistancesCasted; ++node)
        {
            if (node == currentNode.getNextNodes()[node] && node != currentNode.getID())
            {
                if (!visited[node])
                {
                    nodesQueue.push_back(node);
                }

                int new_distance = originDistances[currentNode.getID()] + currentNode.getDistances()[node];

                if (originDistances[node] > new_distance)
                {
                    this->changeRoute(nodeID, currentNode.getID(), node, new_distance);
                }
            }
        }
        visited[currentNode.getID()] = true;
    }
    hasRoutes[nodeID] = true;
}

std::vector<int> Graph::getRoute(int start, int end)
{
    std::vector<int> result;
    while (start != end)
    {
        result.push_back(start);
        start = nodes[start].getNextNodes()[end];
    }
    result.push_back(end);
    return result;
}

std::vector<Node> &Graph::getNodes()
{
    return nodes;
}

std::vector<int> Graph::findClassrooms(const std::string &className) const
{
    std::vector<int> found_classrooms;
    for (const Node &node : nodes)
    {
        if (node.findClassroom(className))
        {
            found_classrooms.push_back(node.getID());
        }
    }
    return found_classrooms;
}

int Graph::getDistance(int start, int end)
{
    int resultDistance = nodes[start].getDistances()[end];
    return resultDistance;
}