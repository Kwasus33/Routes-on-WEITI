#pragma once

#include "logic_manager.hpp"
#include "console_interface.hpp"
#include "resource_manager.hpp"
#include "input_manager.hpp"
#include "renderer.hpp"
#include "user_action.hpp"

class InputManager;
class ConsoleInterface;

class ProgramManager
{
    ResourceManager* resourceManager;
    InputManager* inputManager;
    LogicManager* logicManager;
    Renderer* renderer;
    ConsoleInterface* consoleInterface;
    
    bool isShowing;

public:
    ProgramManager();
    ~ProgramManager();
    void Run(Action nextAction = Action::NONE, std::string room1 = "", std::string room2 = "");
    void StopShowing();

private:
    void Init();
    

};