#pragma once

#include "program_manager.hpp"

class ProgramManager;
class LogicManager;
class InputManager;

class Command
{
public:
    virtual ~Command() {};
    virtual void execute() = 0; 
};

class QuitCommand : public Command
{
    ProgramManager* programManager;
public:
    QuitCommand(ProgramManager* programManager);
    void execute() override;
};

class FloorUpCommand : public Command
{
    LogicManager* logicManager;
public:
    FloorUpCommand(LogicManager* logicManager);
    void execute() override;
};

class FloorDownCommand : public Command
{
    LogicManager* logicManager;
public:
    FloorDownCommand(LogicManager* logicManager);
    void execute() override;
};