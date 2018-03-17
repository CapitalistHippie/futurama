#ifndef FUTURAMA_FUT_UI_COMMAND_H_INCLUDED
#define FUTURAMA_FUT_UI_COMMAND_H_INCLUDED

namespace fut::ui
{
struct Command
{
    char name[64];

    unsigned int argumentCount = 0;
    char arguments[64][64];
}; // struct Command
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_COMMAND_H_INCLUDED
