#pragma once

#include "resource_manager.hpp"
#include "input_manager.hpp"
#include "logic_manager.hpp"
#include "renderer.hpp"

class ProgramManager
{
    ResourceManager* resourceManager;
    InputManager* inputManager;
    LogicManager* logicManager;
    Renderer* renderer;

public:
    ProgramManager();
    void Run();

private:
    void Init();

};