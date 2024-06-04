#pragma once
#include <vector>

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


class argParser
{
public:
    argParser(int argc, char *argv[]);
    void parseArguments(int argc, char *argv[]);
private:
    int argc;
    char **argv;
    ParserState state;
    void parseGUI();
    void parseTUI(int argc, char *argv[]);
};