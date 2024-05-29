#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isRunning(true)
{
    logicManager = new LogicManager();
    inputManager = new InputManager(this, logicManager);
    renderer = new Renderer();
    resourceManager = new ResourceManager(renderer);
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