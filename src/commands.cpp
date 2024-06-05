#include "commands.hpp"

QuitCommand::QuitCommand(ProgramManager *programManager)
    : programManager(programManager) {}

void QuitCommand::execute()
{
    programManager->stopShowing();
}

FloorUpCommand::FloorUpCommand(LogicManager *logicManager)
    : logicManager(logicManager) {}

void FloorUpCommand::execute()
{
    logicManager->changeFloor(1);
}

FloorDownCommand::FloorDownCommand(LogicManager *logicManager)
    : logicManager(logicManager) {}

void FloorDownCommand::execute()
{
    logicManager->changeFloor(-1);
}