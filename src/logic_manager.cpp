#include "logic_manager.hpp"

#include "file_handler.hpp"
#include "config.hpp"

LogicManager::LogicManager()
    : currentFloor(0)
{
    jsonReader fh("../test/test.json");
    graph = fh.ReadDataIntoGraph();
}

void LogicManager::UpdatePath()
{

}

void LogicManager::ChangeFloor(int change)
{
    currentFloor += change;
    if (currentFloor < config::MIN_FLOOR || currentFloor > config::MAX_FLOOR)
    {
        currentFloor -= change;
    }
}