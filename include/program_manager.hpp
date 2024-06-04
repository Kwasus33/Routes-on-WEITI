#pragma once

#include "logic_manager.hpp"
#include "console_interface.hpp"
#include "resource_manager.hpp"
#include "input_manager.hpp"
#include "renderer.hpp"
#include "user_action.hpp"
#include <memory>

class InputManager;
class ConsoleInterface;

class ProgramManager
{
    std::unique_ptr<ResourceManager> resourceManager;
    std::unique_ptr<InputManager> inputManager;
    std::unique_ptr<LogicManager> logicManager;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<ConsoleInterface> consoleInterface;
    
    bool isShowing;

public:
    ProgramManager();
    void Run(Action nextAction = Action::NONE, std::string room1 = "", std::string room2 = "");
    void StopShowing();

private:
    void Init();
    

};