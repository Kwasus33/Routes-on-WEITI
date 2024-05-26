#pragma once
#include <iostream>
#include <vector>
#include "classroom.hpp"
#include <limits>

class Node
{
public:
    Node(const int ID, std::vector<int>& dist, std::vector<int>& connected, const int floor, const int X, const int Y);
    int getID() const;
    std::vector<int> &getDistances();
    std::vector<int> &getNextNodes();
    std::vector<Classroom> &getClassrooms();
    void setDistance(const int nodeID, const int distance);
    void addRoute(const int ID, const int distance, const int nextNode);
    void setNextNode(const int toNode, const int nextNode);
    void addClassroom(Classroom &new_classroom);
    bool findClassroom(std::string &class_name) const;
    int getX() const;
    int getY() const;
    int getFloor() const;
    void setX(const int x);
    void setY(const int y);
    void setFloor(const int floor);

private:
    int ID;
    std::vector<int> distances;
    std::vector<int> nextNodes;
    std::vector<Classroom> classrooms;
    int X;
    int Y;
    int floor;
};