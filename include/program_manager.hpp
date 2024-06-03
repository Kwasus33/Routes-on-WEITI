#pragma once

#include "resource_manager.hpp"
#include "input_manager.hpp"
#include "logic_manager.hpp"
#include "renderer.hpp"
#include "console_interface.hpp"

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
    void Run();
    void StopShowing();

private:
    void Init();
    

};