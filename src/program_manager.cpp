#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isShowing(true)
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
    while(isShowing)
    {
        inputManager->Update();
        renderer->Render(resourceManager, logicManager->GetCurrentFloor());
    }
}

void ProgramManager::StopShowing()
{
    isShowing = false;
}