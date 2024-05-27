#include "input_manager.hpp"

InputManager::InputManager(ProgramManager* programManager)
    : programManager(manager) 
{
    commandMap[InputType::QUIT] = new QuitCommand(manager);
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