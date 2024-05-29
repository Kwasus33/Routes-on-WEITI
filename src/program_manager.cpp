#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isRunning(true)
{
    renderer = new Renderer();
    resourceManager = new ResourceManager(renderer);
    logicManager = new LogicManager(resourceManager);
    inputManager = new InputManager(this, logicManager);
}

ProgramManager::~ProgramManager()
{
    delete inputManager;
    delete logicManager;
    delete renderer;
    delete resourceManager;
}

void ProgramManager::Run()
{
    Init();

    while(isRunning)
    {
        inputManager->Update();
        renderer->Render(resourceManager);
    }
}

void ProgramManager::Stop()
{
    isRunning = false;
}

void ProgramManager::Init()
{
}