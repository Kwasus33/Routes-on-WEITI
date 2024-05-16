#pragma once
#include <iostream>
#include <vector>
#include "classroom.hpp"
#include <limits>

class Node{
    public:
    Node(int ID, std::vector<int> dist, std::vector<int> connected, int floor, int X, int Y);
    int getID() const;
    std::vector<int>& getDistances();
    std::vector<int>& getNextNodes();
    std::vector<Classroom>& getClassrooms();
    void setDistance(int nodeID, int distance);
    void addRoute(int ID, int distance, int nextNode);
    void setNextNode(int toNode, int nextNode);
    void addClassroom(Classroom& new_classroom);
    bool findClassroom(std::string& class_name);
    int getX() const;
    int getY() const;
    int getFloor() const;
    void setX(int x);
    void setY(int y);
    void setFloor(int floor);
    private:
    int ID;
    std::vector<int> distances;
    std::vector<int> nextNodes;
    std::vector<Classroom> classrooms;
    int X;
    int Y;
    int floor;
};