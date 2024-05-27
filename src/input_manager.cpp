#include "input_manager.hpp"

InputManager::InputManager(ProgramManager* programManager)
    : programManager(manager) 
{
    commandMap[InputType::QUIT] = new QuitCommand(manager);
}

InputManager::~InputManager()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            commandMap[InputType::QUIT]->Execute();
        }
    }
}

void InputManager::Update()
{
    if (event.type == SDL_KEYDOWN) 
    {
        auto it = commandMap.find(event.key.keysym.sym);
        if (it != commandMap.end()) 
        {
            it->second->execute();
        }
    }
}