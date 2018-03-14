#include "fut/ui/commandparser.h"

using namespace fut::ui;

Command CommandParser::ParseCommand(std::istream& inputStream) const
{
    Command command;

    char commandLine[64];
    inputStream.getline(commandLine, 64);

    char* locationPtr = strchr(commandLine, ' ');
    if (locationPtr == nullptr)
    {
        strcpy(command.name, commandLine);
    }
    else
    {
        int location = locationPtr - commandLine + 1;
        strncpy(command.name, commandLine, location - 1);
        command.name[location - 1] = '\0';
    }

    return command;
}
