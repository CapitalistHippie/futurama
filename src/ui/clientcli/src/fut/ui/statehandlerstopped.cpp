#include "fut/ui/statehandlerstopped.h"

#include <functional>

#include <fut/domain/events/gamestarted.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlerheadquarters.h"

using namespace fut::ui;

void StateHandlerStopped::StartCommandHandler() const
{
    client->StartGame();
}

void StateHandlerStopped::GameStartedEventHandler() const
{
    context->SetStateHandler<StateHandlerHeadquarters>();
}

void StateHandlerStopped::ExitStateBase() noexcept
{
}

void StateHandlerStopped::EnterState()
{
    RegisterCommandObserver("start", std::bind(&StateHandlerStopped::StartCommandHandler, this));

    RegisterEventObserver<domain::events::GameStarted>(std::bind(&StateHandlerStopped::GameStartedEventHandler, this));

    infra::ClearCli();
    *outputStream << "Welcome to Futurama: Planet Express!\n\n";

    *outputStream << "Available commands.\n"
                  << "start\t\t\t-- Start the game.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";
}
