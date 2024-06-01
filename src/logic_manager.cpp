#include "logic_manager.hpp"

#include "file_handler.hpp"
#include "config.hpp"

LogicManager::LogicManager(ResourceManager* resourceManager)
    : currentFloor(0), resourceManager(resourceManager)
{
    std::vector<std::string> path {"../assets/Floor1.json", "../assets/Floor0.json"};
    jsonReader fh(path);
    graph = fh.ReadDataIntoGraph();
}

void LogicManager::UpdatePath(std::string& start, std::string& end)
{
<<<<<<< HEAD
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
=======
    // Tries to find classrooms with given names
    std::vector<int> startSearches = graph.findClassrooms(start);
    std::vector<int> endSearches = graph.findClassrooms(end);
    // If no classrooms are found, throws an exception
    if (startSearches.empty() || endSearches.empty())
        throw std::invalid_argument("Classroom not found");
    // If multiple classrooms are found, chooses the first one for start
    int startID = startSearches[0];
    graph.findRoutes(startID);
    // If multiple classrooms are found, chooses the one that is the closest to start
    std::sort(endSearches.begin(), endSearches.end(), [&startID, this](int nodeOne, int nodeTwo)
              { return graph.getDistance(startID, nodeOne) < graph.getDistance(startID, nodeTwo); });
    int endID = endSearches[0];
>>>>>>> 2a0549c98ada99b98da7e09a7cd14dd29e505d7e
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