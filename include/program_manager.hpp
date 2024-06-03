#pragma once

#include "resource_manager.hpp"
#include "input_manager.hpp"
#include "logic_manager.hpp"
#include "renderer.hpp"

class InputManager;

class ProgramManager
{
    ResourceManager* resourceManager;
    InputManager* inputManager;
    LogicManager* logicManager;
    Renderer* renderer;
    
    bool isShowing;

public:
    ProgramManager();
    ~ProgramManager();
    void Run();
    void StopShowing();

private:
    void Init();
    

};