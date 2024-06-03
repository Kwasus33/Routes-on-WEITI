#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isShowing(true)
{
    renderer = new Renderer();
    resourceManager = new ResourceManager(renderer);
    logicManager = new LogicManager(resourceManager);
    inputManager = new InputManager(this, logicManager);
    consoleInterface = new ConsoleInterface(logicManager);
}

ProgramManager::~ProgramManager()
{
    delete inputManager;
    delete logicManager;
    delete renderer;
    delete resourceManager;
    delete logicManager;
}

void ProgramManager::Run()
{
    Action nextAction;
    do
    {
        nextAction = consoleInterface->GetNextAction();

        switch (nextAction)
        {
        case Action::SHOW_DESCRIPTION:
            // consoleInterface->ShowDescription();
            break;

        case Action::SHOW_PATH:

            consoleInterface->SetNewPath();
            renderer->ShowWindow();
            isShowing = true;
            while(isShowing)
            {
                inputManager->Update();
                renderer->Render(resourceManager, logicManager->GetCurrentFloor());
            }
            renderer->HideWindow();
            break;
        }
    } while(nextAction != Action::QUIT);
    
}

void ProgramManager::StopShowing()
{
    isShowing = false;
}