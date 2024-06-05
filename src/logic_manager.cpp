#include "logic_manager.hpp"
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include "config.hpp"

LogicManager::LogicManager(ResourceManager* resourceManager)
    : currentFloor(0), resourceManager(resourceManager)
{
    std::vector<std::string> path {"../assets/Floor1.json", "../assets/Floor0.json"};
    JSONReader fh(path);
    graph = fh.readDataIntoGraph();
}

void LogicManager::updatePath(std::string& start, std::string& end)
{
    // Tries to find classrooms with given names
    std::vector<int> startSearches = graph.findClassrooms(start);
    std::vector<int> endSearches = graph.findClassrooms(end);
    // If no classrooms are found, throws an exception
    if (startSearches.empty() || endSearches.empty()){
        throw std::invalid_argument("Classroom not found");
    }
    // If multiple classrooms are found, chooses the first one for start
    int startID = startSearches[0];
    graph.findRoutes(startID);
    // If multiple classrooms are found, chooses the one that is the closest to start
    std::sort(endSearches.begin(), endSearches.end(), [&startID, this](int nodeOne, int nodeTwo)
              { return graph.getDistance(startID, nodeOne) < graph.getDistance(startID, nodeTwo); });
    int endID = endSearches[0];
    std::vector<int> path = graph.getRoute(startID, endID);
    resourceManager->setPathFromGraph(&graph, path);
}

std::string LogicManager::getDescription(std::string className)
{
    std::vector<int> classIDs = graph.findClassrooms(className);
    if(classIDs.empty()){
        throw std::invalid_argument("Classroom not found");
    }
    int classID = classIDs[0];
    std::vector<Node>& nodes = graph.getNodes();
    for (const auto& clss : nodes[classID].getClassrooms())
    {
        if(clss.getName() == className) return clss.getDescription();
    }
    throw std::invalid_argument("Classroom not found");
}

void LogicManager::changeFloor(int change)
{
    currentFloor += change;
    if (currentFloor < config::MIN_FLOOR || currentFloor > config::MAX_FLOOR)
    {
        currentFloor -= change;
        return;
    }
}