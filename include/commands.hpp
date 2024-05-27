#pragma once

#include "program_manager.hpp"

class ProgramManager;

class Command
{
public:
    virtual ~Command() {};
    virtual void Execute() = 0; 
};

class QuitCommand : public Command
{
    ProgramManager* programManager;
public:
    QuitCommand(ProgramManager* programManager);
    void Execute() override;
};