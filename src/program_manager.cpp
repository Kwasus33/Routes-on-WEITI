#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isRunning(true)
{
    resourceManager = new ResourceManager();
    inputManager = new InputManager(this);
    renderer = new Renderer(800, 600);
}

ProgramManager::~ProgramManager()
{
    delete resourceManager;
    delete inputManager;
    delete renderer;
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