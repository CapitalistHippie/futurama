#include "fut/ui/statehandlerheadquarters.h"

#include <functional>

#include <fut/infra/clihelpers.h>

using namespace fut::ui;

void StateHandlerHeadquarters::ExitStateBase() noexcept
{
}

void StateHandlerHeadquarters::EnterState()
{
    infra::ClearCli();
    *outputStream << "You're in the headquarters. Pick a sector from the scan to start in.\n";
}
