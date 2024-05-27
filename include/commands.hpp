#pragma once

#include "program_manager.hpp"

class Command
{
public:
    virtual ~Command() {};
    virtual void Execute() = 0; 
};

class QuitCommand : Command
{
    ProgramManager* programManager;
public:
    QuitCommand(ProgramManager* programManager)
        : programManager(programManager) {}
    void Execute() override 
        { programManager->Stop(); }
};