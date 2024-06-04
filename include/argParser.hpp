#pragma once
#include <vector>

enum class ParserState {
    BEGIN,
    TUI,
    GUI    
};

enum class TuiCommand {
    FIND_PATH,
    FIND_CLASSROOM,
    QUIT
};


class argParser
{
public:
    argParser(int argc, char *argv[]);
    std::vector<std::string> parseArguments(int argc, char *argv[]);
private:
    int argc;
    char **argv;
    ParserState state;
    void defineState();
};