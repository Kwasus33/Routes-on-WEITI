#include "program_manager.hpp"

ProgramManager::ProgramManager()
{

}

void ProgramManager::Run()
{
    Init();

    while(true)
    {
        inputManager.Update();
        logicManager.Update();
        renderer.Render();
    }
}

void ProgramManager::Init()
{
    resourceManager.LoadFloors();
}