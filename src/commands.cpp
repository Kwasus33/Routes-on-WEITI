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

UpdatePathCommand::UpdatePathCommand(LogicManager* logicManager, InputManager* inputManager)
    : logicManager(logicManager), inputManager(inputManager) {}

void UpdatePathCommand::Execute()
{
    // std::string input = inputManager->GetText();
    // int split = input.find(':');
    // std::string start = input.substr(0, split);
    // std::string end = input.substr(split+1, input.length());
    // logicManager->UpdatePath(start, end);
}