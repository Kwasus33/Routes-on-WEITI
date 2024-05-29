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
    
    bool isRunning;

public:
    ProgramManager();
    ~ProgramManager();
    void Run();
    void Stop();

    //TODO replace with ui
    void setgraph(std::string uno, std::string dos)
    {
        logicManager->UpdatePath(uno, dos);
    }

private:
    void Init();
    

};