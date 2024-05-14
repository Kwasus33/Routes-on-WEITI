#pragma once
#include <iostream>
#include <vector>
#include "classroom.hpp"

class Node{
    public:
    Node(int ID, std::vector<int> dist);
    int getID() const;
    std::vector<int>& getDistances();
    std::vector<int>& getNextNodes();
    std::vector<Classroom>& getClassrooms();
    void setDistance(int nodeID, int distance);
    void addRoute(int ID, int distance, int nextNode);
    void setNextNode(int toNode, int nextNode);
    void addClassroom(Classroom& new_classroom);
    bool findClassroom(std::string& class_name);
    private:
    int ID;
    std::vector<int> distances;
    std::vector<int> nextNodes;
    std::vector<Classroom> classrooms;
};