#include "node.hpp"
#include <algorithm>

Node::Node(int ID, std::vector<int> dist, std::vector<int> connected, int floor, int X, int Y) : ID(ID), X(X), Y(Y)
{
    if (connected.size() != 0)
    {

        int lastNode = connected[connected.size() - 1];
        int size = 0;
        int current_index = 0;
        while (size <= lastNode)
        {
            if (size == connected[current_index] && size != ID)
            {
                distances.push_back(dist[current_index]);
                nextNodes.push_back(connected[current_index]);
                ++current_index;
            }
            else
            {
                if (size == ID)
                {
                    distances.push_back(0);
                    nextNodes.push_back(ID);
                }
                else
                {
                    distances.push_back(__INT_MAX__);
                    nextNodes.push_back(-1);
                }
            }

            ++size;
        }
    }

    while (nextNodes.size() <= ID)
    {
        if (nextNodes.size() == ID)
        {
            distances.push_back(0);
            nextNodes.push_back(ID);
        }
        else
        {
            distances.push_back(__INT_MAX__);
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
    int current_length = distances.size();
    while (current_length < nodeID)
    {
        ++current_length;
        if (current_length - 1 == ID)
        {
            distances.push_back(0);
            nextNodes.push_back(ID);
        }
        else
        {
            distances.push_back(__INT_MAX__);
            nextNodes.push_back(-1);
        }
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

void Node::addClassroom(Classroom &new_classroom)
{
    classrooms.push_back(new_classroom);
}

std::vector<Classroom> &Node::getClassrooms()
{
    return classrooms;
}

bool Node::findClassroom(std::string &className)
{
    return classrooms.end() != std::find_if(classrooms.begin(), classrooms.end(), [&className](Classroom classroom)
                                            { return className == classroom.getName(); });
}
int Node::getX() const
{
    return X;
}

int Node::getY() const
{
    return Y;
}

int Node::getFloor() const
{
    return floor;
}

void Node::setX(int x)
{
    X = x;
}

void Node::setY(int y)
{
    Y = y;
}

void Node::setFloor(int floor)
{
    this->floor = floor;
}