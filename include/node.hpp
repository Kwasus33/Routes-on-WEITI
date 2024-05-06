#include <iostream>
#include <vector>

class Node{
    public:
    Node(int ID, std::vector<int> dist);
    int getID() const;
    std::vector<int>& getDistances();
    std::vector<int>& getNextNodes();
    void setDistance(int nodeID, int distance);
    void addRoute(int ID, int distance, int nextNode);
    void setNextNode(int toNode, int nextNode);
    private:
    int ID;
    std::vector<int> distances;
    std::vector<int> nextNodes;
};