#include "input_manager.hpp"

InputManager::InputManager(ProgramManager* programManager, LogicManager* LogicManager)
{
    commandMap[InputType::QUIT] = new QuitCommand(programManager);
    commandMap[InputType::FLOOR_UP] = new FloorUpCommand(LogicManager);
    commandMap[InputType::FLOOR_DOWN] = new FloorDownCommand(LogicManager);
    commandMap[InputType::UPDATE_PATH] = new UpdatePathCommand(LogicManager, this);

    SDL_StartTextInput();
}

InputManager::~InputManager()
{
    for (auto item : commandMap) 
    {
        delete item.second;
    }

    SDL_StopTextInput();
}

void InputManager::Update()
{
    bool updatedText = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            commandMap[InputType::QUIT]->Execute();
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                commandMap[InputType::QUIT]->Execute();
            }
            else if(event.key.keysym.sym == SDLK_UP) {
                commandMap[InputType::FLOOR_UP]->Execute();
            }
            else if(event.key.keysym.sym == SDLK_DOWN) {
                commandMap[InputType::FLOOR_DOWN]->Execute();
            }
            else if(event.key.keysym.sym == SDLK_BACKSPACE) {
                text = text.substr(0, text.length()-1);
                updatedText = true;
            }
            else if(event.key.keysym.sym == SDLK_KP_ENTER) {
                commandMap[InputType::UPDATE_PATH]->Execute();
            }
        }
        else if(event.type == SDL_TEXTINPUT) {
            text += event.text.text;
            updatedText = true;
        }
    }

    if(updatedText)
    {
        //TODO clear console for each input???
        std::cout << text << std::endl;
    }
}