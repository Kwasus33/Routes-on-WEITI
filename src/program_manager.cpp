#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isRunning(true)
{
    inputManager = new InputManager(this);
    renderer = new Renderer(800, 600);
}

ProgramManager::~ProgramManager()
{
    delete inputManager;
}

void ProgramManager::Run()
{
    Init();

    while(isRunning)
    {
        inputManager->Update();
        // logicManager->Update();
        renderer->Render();
    }
}

void ProgramManager::Stop()
{
    isRunning = false;
}

void ProgramManager::Init()
{
}