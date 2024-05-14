#include "node.hpp"
#include <algorithm>

Node::Node(int ID, std::vector<int> dist) : ID(ID), distances(dist) {
    while (nextNodes.size() != distances.size())
    {
        int currentIndex = nextNodes.size();
        if (distances[currentIndex] != __INT_MAX__)
        {
            nextNodes.push_back(currentIndex);
        }
        else
        {
            nextNodes.push_back(-1);
        }
    }
}

int Node::getID() const
{
    return ID;
}

std::vector<int> &Node::getDistances()
{
    return distances;
}

std::vector<int> &Node::getNextNodes()
{
    return nextNodes;
}

void Node::setDistance(int nodeID, int distance)
{
    if (nodeID < distances.size())
    {
        distances[nodeID] = distance;
        return;
    }
    while (distances.size() - 1 < nodeID)
    {
        distances.push_back(__INT_MAX__);
        nextNodes.push_back(-1);
    }
    distances.push_back(distance);
    nextNodes.push_back(-1);
}

void Node::setNextNode(int toNode, int nextNode)
{
    nextNodes[toNode] = nextNode;
}

void Node::addRoute(int ID, int distance, int nextNode)
{
    this->setDistance(ID, distance);
    this->setNextNode(ID, nextNode);
}

void Node::addClassroom(Classroom& new_classroom)
{
    classrooms.push_back(new_classroom);
}

std::vector<Classroom>& Node::getClassrooms()
{
    return classrooms;
}

bool Node::findClassroom(std::string& className)
{
    return classrooms.end() != std::find_if(classrooms.begin(), classrooms.end(), [&className](Classroom classroom){return className == classroom.getName();});
}