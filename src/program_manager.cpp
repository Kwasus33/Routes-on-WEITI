#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isRunning(true), inputManager(this)
{
}

void ProgramManager::Run()
{
    Init();

    while(isRunning)
    {
        inputManager.Update();
        logicManager.Update();
        renderer.Render();
    }
}

void ProgramManager::Stop()
{
    isRunning = false;
}

void ProgramManager::Init()
{
}