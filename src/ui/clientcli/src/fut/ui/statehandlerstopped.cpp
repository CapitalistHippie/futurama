#include "fut/ui/statehandlerstopped.h"

#include <functional>

#include "fut/ui/command.h"

using namespace fut::ui;

void StateHandlerStopped::StartCommandHandler() const
{
    client->StartGame();
}

void StateHandlerStopped::EnterState()
{
    commandSubject->RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "start") == 0; },
      std::bind(&StateHandlerStopped::StartCommandHandler, this));

    *outputStream << "Welcome to Futurama: Planet Express!\n"
                  << "Enter 'start' to start the game.\n";
}

void StateHandlerStopped::ExitStateBase() noexcept
{
}
