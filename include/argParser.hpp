#pragma once
#include <vector>
#include <string>
#include <list>

enum class ParserState {
    BEGIN,
    TUI,
    GUI    
};

enum class TuiCommand {
    BEGIN,
    FIND_PATH,
    FIND_CLASSROOM,
    QUIT
};


class ArgParser
{
public:
    ArgParser(int argc, char *argv[]);
    ParserState parseArguments(int argc, char *argv[]);
    std::list<std::string> parseTUI();
    TuiCommand getState() const;
private:
    int argc;
    char **argv;
    ParserState state;
    TuiCommand command;
};