#include "program_manager.hpp"

ProgramManager::ProgramManager()
    : isShowing(true)
{
    renderer = std::make_unique<Renderer>();
    resourceManager = std::make_unique<ResourceManager>(renderer.get());
    logicManager = std::make_unique<LogicManager>(resourceManager.get());
    inputManager = std::make_unique<InputManager>(this, logicManager.get());
    consoleInterface = std::make_unique<ConsoleInterface>(logicManager.get());
}

void ProgramManager::run(Action nextAction, std::string room1, std::string room2)
{
    do
    {
        switch (nextAction)
        {
        case Action::SHOW_DESCRIPTION:
            consoleInterface->ShowDescription(room1);
            break;

        case Action::SHOW_PATH:
            consoleInterface->SetNewPath(room1, room2);
            renderer->showWindow();
            isShowing = true;
            while (isShowing)
            {
                inputManager->update();
                renderer->render(resourceManager.get(), logicManager->getCurrentFloor());
            }
            renderer->hideWindow();
            break;

        default:
            break;
        }

        nextAction = consoleInterface->getNextAction();
        room1 = "";
        room2 = "";
    } while (nextAction != Action::QUIT);
}

void ProgramManager::stopShowing()
{
    isShowing = false;
}