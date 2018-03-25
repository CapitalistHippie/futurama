#include "fut/ui/statehandlerinencounter.h"

#include <cmath>
#include <functional>

#include <fut/domain/events/shiprepaired.h>
#include <fut/domain/models/encounterconsequence.h>
#include <fut/domain/models/encounterinstance.h>
#include <fut/infra/clihelpers.h>

using namespace fut::ui;

void StateHandlerInEncounter::ExitStateBase() noexcept
{
}

void StateHandlerInEncounter::ContinueCommandHandler() const
{
}

void fut::ui::StateHandlerInEncounter::ShipRepairedGameEventHandler() const
{
}

void StateHandlerInEncounter::PrintCli(const char* extra) const
{
    const domain::models::EncounterInstance& encounter = *client->GetGame().GetData().encounterInstance;

    infra::ClearCli();
    *outputStream << "Your encounter with " << encounter.description << " resulted in ";

    switch (encounter.consequence)
    {
        case domain::models::EncounterConsequence::Battle:
            *outputStream << "a battle!";
            break;
        case domain::models::EncounterConsequence::Nothing:
            *outputStream << "nothing.";
            break;
        case domain::models::EncounterConsequence::Repair:
            *outputStream << "them repairing your ship.";
            break;
        case domain::models::EncounterConsequence::VictoryPoints:
            if (encounter.victoryPoints > 0)
            {
                *outputStream << "you gaining " << encounter.victoryPoints << " victory points!";
            }
            else
            {
                *outputStream << "you losing " << abs(encounter.victoryPoints) << " victory points.";
            }
            break;
    }

    if (strcmp(encounter.consequenceText, "") != 0)
    {
        *outputStream << '\n' << encounter.consequenceText;
    }

    *outputStream << "\n\n";

    *outputStream << "Available commands.\n"
                  << "continue\t\t-- Continue with your journey.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerInEncounter::EnterState()
{
    RegisterCommandObserver("continue", std::bind(&StateHandlerInEncounter::ContinueCommandHandler, this));

    RegisterGameEventObserver<domain::events::ShipRepaired>(
      std::bind(&StateHandlerInEncounter::ShipRepairedGameEventHandler, this));

    PrintCli();
}
