#include "logic_manager.hpp"

#include "file_handler.hpp"
#include "config.hpp"

LogicManager::LogicManager(ResourceManager* resourceManager)
    : currentFloor(0), resourceManager(resourceManager)
{
    std::vector<std::string> path {"../test/test.json"};
    jsonReader fh(path);
    graph = fh.ReadDataIntoGraph();
}

void LogicManager::UpdatePath(std::string& start, std::string& end)
{
    int startID = graph.findClassroom(start);
    if(startID == -1)
    {
        std::cout << "Couldn't find class: " << start << std::endl;
        return;
    }
    int endID = graph.findClassroom(end);
    if(endID == -1)
    {
        std::cout << "Couldn't find class: " << end << std::endl;
        return;
    }
    
    graph.findRoutes(startID);
    std::vector<int> path = graph.getRoute(startID, endID);
    resourceManager->GetPath().SetFromGraph(&graph, path);
}

void LogicManager::ChangeFloor(int change)
{
    currentFloor += change;
    if (currentFloor < config::MIN_FLOOR || currentFloor > config::MAX_FLOOR)
    {
        currentFloor -= change;
        return;
    }
}