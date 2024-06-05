#include "input_manager.hpp"

InputManager::InputManager(ProgramManager *programManager, LogicManager *LogicManager)
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

void InputManager::update()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            commandMap[InputType::QUIT]->execute();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                commandMap[InputType::QUIT]->execute();
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                commandMap[InputType::FLOOR_UP]->execute();
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                commandMap[InputType::FLOOR_DOWN]->execute();
            }
        }
    }
}