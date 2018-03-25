#include "fut/ui/statehandlerpickingmeetingcharacter.h"

#include <functional>

#include <fut/domain/models/character.h>
#include <fut/domain/models/gamestate.h>
#include <fut/infra/clihelpers.h>

//#include "fut/ui/statehandlerheadquarters.h"

using namespace fut::ui;

void StateHandlerPickingMeetingCharacter::ExitStateBase() noexcept
{
}

void StateHandlerPickingMeetingCharacter::PickCommandHandler(const Command& command) const
{
    if (command.argumentCount < 1)
    {
        PrintCli("Too few arguments.");
        return;
    }

    if (strcmp(command.arguments[0], "fry") == 0)
    {
        client->PickEncounterNegotiator(domain::models::Character::Fry);
    }
    else if (strcmp(command.arguments[0], "leela") == 0)
    {
        client->PickEncounterNegotiator(domain::models::Character::Leela);
    }
    else if (strcmp(command.arguments[0], "bender") == 0)
    {
        client->PickEncounterNegotiator(domain::models::Character::Bender);
    }
    else
    {
        PrintCli("Unknown character.");
    }
}

void fut::ui::StateHandlerPickingMeetingCharacter::StateChangedGameEventHandler(
  const domain::events::StateChanged& evt) const
{
    if (evt.newState != domain::models::GameState::InMeeting)
    {
        return;
    }

    // context->SetStateHandler<StateHandlerHeadquarters>();
}

void StateHandlerPickingMeetingCharacter::PrintCli(const char* extra) const
{
    infra::ClearCli();
    *outputStream << "You encountered " << client->GetGame().GetData().meeting->description
                  << "! Pick either Fry, Leela or Bender to deal with the situation.\n\n";

    *outputStream << "Available commands.\n"
                  << "pick <character>\t-- Pick a character.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerPickingMeetingCharacter::EnterState()
{
    RegisterCommandObserver(
      "pick", std::bind(&StateHandlerPickingMeetingCharacter::PickCommandHandler, this, std::placeholders::_1));

    RegisterGameEventObserver<domain::events::StateChanged>(
      std::bind(&StateHandlerPickingMeetingCharacter::StateChangedGameEventHandler, this, std::placeholders::_1));

    PrintCli();
}
