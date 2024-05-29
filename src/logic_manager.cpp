#include "logic_manager.hpp"

#include "file_handler.hpp"
#include "config.hpp"

LogicManager::LogicManager(ResourceManager* resourceManager)
    : currentFloor(0), resourceManager(resourceManager)
{
    jsonReader fh("../test/test.json");
    graph = fh.ReadDataIntoGraph();
}

void LogicManager::UpdatePath(std::string& start, std::string& end)
{
    int startID = graph.findClassroom(start);
    int endID = graph.findClassroom(end);
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

    for (int i = config::MIN_FLOOR; i <= config::MAX_FLOOR; ++i)
    {
        Floor& floor = resourceManager->GetFloor(i);
        SDL_Rect t = floor.GetTransfrom();
        t.y -= change*config::SCREEN_HEIGHT;
        floor.SetTransfrom(t);
    }
}