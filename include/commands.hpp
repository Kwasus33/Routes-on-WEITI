#pragma once

#include "program_manager.hpp"

class ProgramManager;
class LogicManager;
class InputManager;

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

class FloorUpCommand : public Command
{
    LogicManager* logicManager;
public:
    FloorUpCommand(LogicManager* logicManager);
    void Execute() override;
};

class FloorDownCommand : public Command
{
    LogicManager* logicManager;
public:
    FloorDownCommand(LogicManager* logicManager);
    void Execute() override;
};

class UpdatePathCommand : public Command
{
    LogicManager* logicManager;
    InputManager* inputManager;
public:
    UpdatePathCommand(LogicManager* logicManager, InputManager* inputManager);
    void Execute() override;
};