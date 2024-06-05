#include "logic_manager.hpp"
#include "jsonReader.hpp"
#include "csvReader.hpp"
#include "config.hpp"

LogicManager::LogicManager(ResourceManager *resourceManager)
    : currentFloor(0), resourceManager(resourceManager)
{
    std::vector<std::string> pathsVec{"../assets/Floor1.json", "../assets/Floor0.json", "../assets/Floor-1.json"};
    std::unique_ptr<FileReader> fh = std::make_unique<JSONReader>(pathsVec);
    graph = fh->readDataIntoGraph();
}

void LogicManager::updatePath(std::string &start, std::string &end)
{

    std::vector<int> startSearches = graph.findClassrooms(start);
    std::vector<int> endSearches = graph.findClassrooms(end);

    if (startSearches.empty() || endSearches.empty())
    {
        throw std::invalid_argument("Classroom not found");
    }

    int startID = startSearches[0];
    graph.findRoutes(startID);

    std::sort(endSearches.begin(), endSearches.end(), [&startID, this](int nodeOne, int nodeTwo)
              { return graph.getDistance(startID, nodeOne) < graph.getDistance(startID, nodeTwo); });

    int endID = endSearches[0];
    std::vector<int> path = graph.getRoute(startID, endID);
    resourceManager->setPathFromGraph(&graph, path);
}

std::string LogicManager::getDescription(std::string className)
{
    std::vector<int> classIDs = graph.findClassrooms(className);
    if (classIDs.empty())
    {
        throw std::invalid_argument("Classroom not found");
    }
    int classID = classIDs[0];
    std::vector<Node> &nodes = graph.getNodes();
    for (const auto &clss : nodes[classID].getClassrooms())
    {
        if (clss.getName() == className)
        {
            return clss.getDescription();
        }
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

int LogicManager::getCurrentFloor() 
{ 
    return currentFloor; 
}
