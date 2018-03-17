#include "fut/ui/statehandlermenu.h"

#include <functional>

#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlerheadquarters.h"

using namespace fut::ui;

void StateHandlerMenu::ExitStateBase() noexcept
{
}

void StateHandlerMenu::StartCommandHandler() const
{
    // TODO: Set state handler based on current client and game state.
    context->SetStateHandler<StateHandlerHeadquarters>();
}

void StateHandlerMenu::PrintCli() const
{
    infra::ClearCli();
    *outputStream << "Welcome to Futurama: Planet Express!\n\n";

    *outputStream << "Available commands.\n"
                  << "start\t\t\t-- Start the game.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";
}

void StateHandlerMenu::EnterState()
{
    RegisterCommandObserver("start", std::bind(&StateHandlerMenu::StartCommandHandler, this));

    PrintCli();
}
