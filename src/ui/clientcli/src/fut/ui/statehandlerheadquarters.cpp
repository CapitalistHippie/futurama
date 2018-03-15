#include "fut/ui/statehandlerheadquarters.h"

#include <functional>

using namespace fut::ui;

void StateHandlerHeadquarters::ExitStateBase() noexcept
{
}

void StateHandlerHeadquarters::EnterState()
{
    *outputStream << "You're in the headquarters. Pick a sector from the scan to start in.\n";
}
