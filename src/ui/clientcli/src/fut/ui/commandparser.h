#ifndef FUTURAMA_FUT_UI_COMMANDPARSER_H_INCLUDED
#define FUTURAMA_FUT_UI_COMMANDPARSER_H_INCLUDED

#include <istream>

#include "fut/ui/command.h"

namespace fut::ui
{
class CommandParser
{
  public:
    Command ParseCommand(std::istream& inputStream) const;
}; // class CommandParser
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_COMMANDPARSER_H_INCLUDED
