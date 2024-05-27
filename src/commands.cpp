#include "commands.hpp"


QuitCommand::QuitCommand(ProgramManager* programManager)
    : programManager(programManager) {}

void QuitCommand::Execute() 
{ 
    programManager->Stop(); 
}