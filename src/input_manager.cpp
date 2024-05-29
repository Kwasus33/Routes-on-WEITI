#include "input_manager.hpp"

InputManager::InputManager(ProgramManager* programManager, LogicManager* LogicManager)
{
    commandMap[InputType::QUIT] = new QuitCommand(programManager);
    commandMap[InputType::FLOOR_UP] = new FloorUpCommand(LogicManager);
    commandMap[InputType::FLOOR_DOWN] = new FloorDownCommand(LogicManager);
}

InputManager::~InputManager()
{
    for (auto item : commandMap) 
    {
        delete item.second;
    }
}

void InputManager::Update()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            commandMap[InputType::QUIT]->Execute();
        }
    }
}