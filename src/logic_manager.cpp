#include "logic_manager.hpp"

#include "file_handler.hpp"

LogicManager::LogicManager()
    : currentFloor(0)
{
    jsonReader fh("../test/test.json");
    graph = fh.ReadDataIntoGraph();
}