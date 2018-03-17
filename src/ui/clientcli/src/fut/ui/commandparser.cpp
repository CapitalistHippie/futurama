#include "fut/ui/commandparser.h"

using namespace fut::ui;

Command CommandParser::ParseCommand(std::istream& inputStream) const
{
    Command command;

    char commandLine[256];
    inputStream.getline(commandLine, 256);

    char* loc = strtok(commandLine, " \n");

    strcpy(command.name, loc);

    for (loc = strtok(nullptr, " \n"); loc != nullptr; loc = strtok(nullptr, " \n"))
    {
        strcpy(command.arguments[command.argumentCount++], loc);
    }

    return command;
}
