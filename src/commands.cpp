#include "commands.hpp"


QuitCommand::QuitCommand(ProgramManager* programManager)
    : programManager(programManager) {}

void QuitCommand::Execute() 
{ 
    programManager->StopShowing(); 
}

FloorUpCommand::FloorUpCommand(LogicManager* logicManager)
    : logicManager(logicManager) {}

void FloorUpCommand::Execute()
{
    logicManager->ChangeFloor(1);
}

FloorDownCommand::FloorDownCommand(LogicManager* logicManager)
    : logicManager(logicManager) {}

void FloorDownCommand::Execute()
{
    logicManager->ChangeFloor(-1);
}