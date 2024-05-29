#include "logic_manager.hpp"

#include "file_handler.hpp"
#include "config.hpp"

LogicManager::LogicManager()
    : currentFloor(0)
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

    for (auto& floor : resourceManager->GetFloors())
    {
        SDL_Rect t = floor.second.GetTransfrom();
        t.y += change*config::SCREEN_HEIGHT;
        floor.second.SetTransfrom(t);
    }
}