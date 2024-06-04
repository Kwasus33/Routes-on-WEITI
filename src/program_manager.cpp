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
    delete consoleInterface;
}

void ProgramManager::Run(Action nextAction = Action::NONE, std::string room1 = "", std::string room2 = "")
{
    do
    {
        if(nextAction == Action::NONE){
            nextAction = consoleInterface->GetNextAction();
        }

        switch (nextAction)
        {
        case Action::SHOW_DESCRIPTION:
            consoleInterface->ShowDescription(room1);
            break;

        case Action::SHOW_PATH:
            consoleInterface->SetNewPath(room1, room2);
            renderer->ShowWindow();
            isShowing = true;
            while (isShowing)
            {
                inputManager->Update();
                renderer->Render(resourceManager, logicManager->GetCurrentFloor());
            }
            renderer->HideWindow();
            break;

        default:
            break;
        }

        nextAction = Action::NONE;
        room1, room2 = "";
    } while (nextAction != Action::QUIT);
}

void ProgramManager::StopShowing()
{
    isShowing = false;
}