#include "fut/ui/statehandlerinencounter.h"

#include <cmath>
#include <functional>

#include <fut/domain/events/shiprepaired.h>
#include <fut/domain/models/encounterconsequence.h>
#include <fut/domain/models/encounterinstance.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlergameend.h"
#include "fut/ui/statehandlerontheway.h"

using namespace fut;
using namespace fut::ui;

void StateHandlerInEncounter::ExitStateBase() noexcept
{
}

void StateHandlerInEncounter::ContinueCommandHandler() const
{
    if (client->GetGame().GetData().gameState == domain::models::GameState::Lose)
    {
        context->SetStateHandler<StateHandlerGameEnd>();
    }
    else
    {
        context->SetStateHandler<StateHandlerOnTheWay>();
    }
}

void StateHandlerInEncounter::ShipRepairedGameEventHandler() const
{
}

void StateHandlerInEncounter::ShipDamagedGameEventHandler(const domain::events::ShipDamaged& evt) const
{
    *outputStream << "Your ship was hit for " << evt.newDamagePoints - evt.oldDamagePoints << " damage!\n";

    if (client->GetGame().GetData().gameState == domain::models::GameState::Lose)
    {
        *outputStream << "Your ship was destroyed.\n";
    }
}

void StateHandlerInEncounter::EnemyHitGameEventHandler(const domain::events::EnemyHit& evt) const
{
    *outputStream << "The enemy was hit! It has been hit " << evt.enemyHitCount << " times.\n";

    if (evt.enemyHitCount == 3)
    {
        *outputStream << "The enemy has been destroyed!\n";
    }
}

void StateHandlerInEncounter::EnemyMissedGameEventHandler(const domain::events::EnemyMissed& evt) const
{
    *outputStream << "The enemy was missed! It has been hit " << evt.enemyHitCount << " times.\n";
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
                  << "continue\t\t-- Continue.\n"
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
    RegisterGameEventObserver<domain::events::ShipDamaged>(
      std::bind(&StateHandlerInEncounter::ShipDamagedGameEventHandler, this, std::placeholders::_1));
    RegisterGameEventObserver<domain::events::EnemyHit>(
      std::bind(&StateHandlerInEncounter::EnemyHitGameEventHandler, this, std::placeholders::_1));
    RegisterGameEventObserver<domain::events::EnemyMissed>(
      std::bind(&StateHandlerInEncounter::EnemyMissedGameEventHandler, this, std::placeholders::_1));

    PrintCli();
}
