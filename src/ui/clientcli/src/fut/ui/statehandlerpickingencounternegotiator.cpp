#include "fut/ui/statehandlerpickingencounternegotiator.h"

#include <functional>

#include <fut/domain/events/encounterstarted.h>
#include <fut/domain/models/character.h>
#include <fut/domain/models/gamestate.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlerinencounter.h"

using namespace fut::ui;

void StateHandlerPickingEncounterNegotiator::ExitStateBase() noexcept
{
}

void StateHandlerPickingEncounterNegotiator::PickCommandHandler(const Command& command) const
{
    if (command.argumentCount < 1)
    {
        PrintCli("Too few arguments.");
        return;
    }

    domain::models::Character negotiator;

    if (strcmp(command.arguments[0], "fry") == 0)
    {
        negotiator = domain::models::Character::Fry;
    }
    else if (strcmp(command.arguments[0], "leela") == 0)
    {
        negotiator = domain::models::Character::Leela;
    }
    else if (strcmp(command.arguments[0], "bender") == 0)
    {
        negotiator = domain::models::Character::Bender;
    }
    else
    {
        PrintCli("Unknown character.");
        return;
    }

    client->PickEncounterNegotiator(negotiator);
}

void fut::ui::StateHandlerPickingEncounterNegotiator::EncounterStartedGameEventHandler() const
{
    context->SetStateHandler<StateHandlerInEncounter>();
}

void StateHandlerPickingEncounterNegotiator::PrintCli(const char* extra) const
{
    infra::ClearCli();
    *outputStream << "You encountered " << client->GetGame().GetData().encounter->description
                  << "! Pick either Fry, Leela or Bender to deal with the situation.\n\n";

    *outputStream << "Available commands.\n"
                  << "pick <character>\t-- Pick a negotiator.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerPickingEncounterNegotiator::EnterState()
{
    RegisterCommandObserver(
      "pick", std::bind(&StateHandlerPickingEncounterNegotiator::PickCommandHandler, this, std::placeholders::_1));

    RegisterGameEventObserver<domain::events::EncounterStarted>(
      std::bind(&StateHandlerPickingEncounterNegotiator::EncounterStartedGameEventHandler, this));

    PrintCli();
}
