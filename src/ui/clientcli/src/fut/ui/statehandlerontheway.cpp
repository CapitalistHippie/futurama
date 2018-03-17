#include "fut/ui/statehandlerontheway.h"

#include <functional>

#include <fut/domain/events/movedtofield.h>
#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlerheadquarters.h"

using namespace fut::ui;

void StateHandlerOnTheWay::ExitStateBase() noexcept
{
}

void fut::ui::StateHandlerOnTheWay::MoveCommandHandler(const Command& command) const
{
    if (command.argumentCount < 1)
    {
        PrintCli("Too few arguments.");
        return;
    }

    if (strcmp(command.arguments[0], "up") == 0)
    {
        client->MoveUp();
    }
    else if (strcmp(command.arguments[0], "right") == 0)
    {
        client->MoveRight();
    }
    else if (strcmp(command.arguments[0], "down") == 0)
    {
        client->MoveDown();
    }
    else if (strcmp(command.arguments[0], "left") == 0)
    {
        client->MoveLeft();
    }
    else
    {
        PrintCli("Invalid direction.");
        return;
    }
}

void StateHandlerOnTheWay::MovedToSectorGameEventHandler() const
{
    PrintCli();
}

void StateHandlerOnTheWay::MovedToFieldGameEventHandler() const
{
    PrintCli();
}

void StateHandlerOnTheWay::MovedToHeadquartersGameEventHandler() const
{
    context->SetStateHandler<StateHandlerHeadquarters>();
}

void StateHandlerOnTheWay::PrintCli(const char* extra) const
{
    infra::ClearCli();
    *outputStream << "You're on the route route to deliver your package. Navigate to the planet you need to deliver "
                     "your package to.\n\n";

    PrintSector();

    *outputStream << "\n\n";

    *outputStream << "Available commands.\n"
                  << "move <direction>\t-- Move to the field up, right, down or left of you.\n"
                  << "pickup\t\t\t-- Pickup a package from the planet next to you.\n"
                  << "examine\t\t\t-- Examine the package.\n"
                  << "deliver\t\t\t-- Deliver the package to the planet next to you.\n"
                  << "nothing\t\t\t-- Do nothing.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerOnTheWay::PrintSector() const
{
    const auto& sector = client->GetGame().GetCurrentSector();
    const auto& ship = client->GetGame().GetData().ship;

    for (unsigned int i = 0; i < sector.RowCount; ++i)
    {
        *outputStream << ' ';

        for (unsigned int ii = 0; ii < sector.ColumnCount; ++ii)
        {
            if (ship.fieldPoint.y == i && ship.fieldPoint.x == ii)
            {
                *outputStream << "P ";

                continue;
            }

            const auto& field = sector.fields[ii][i];

            switch (field.thing)
            {
                case domain::models::SectorFieldThing::Empty:
                    *outputStream << char(250) << ' ';
                    break;
                case domain::models::SectorFieldThing::Asteroid:
                    *outputStream << "O ";
                    break;
                case domain::models::SectorFieldThing::Meeting:
                    *outputStream << "* ";
                    break;
                case domain::models::SectorFieldThing::Planet:
                    *outputStream << "@ ";
                    break;
            }
        }

        if (i != sector.RowCount - 1)
        {
            *outputStream << '\n';
        }
    }
}

void StateHandlerOnTheWay::EnterState()
{
    RegisterCommandObserver("move", std::bind(&StateHandlerOnTheWay::MoveCommandHandler, this, std::placeholders::_1));

    RegisterGameEventObserver<domain::events::MovedToSector>(
      std::bind(&StateHandlerOnTheWay::MovedToSectorGameEventHandler, this));

    RegisterGameEventObserver<domain::events::MovedToField>(
      std::bind(&StateHandlerOnTheWay::MovedToFieldGameEventHandler, this));

    RegisterGameEventObserver<domain::events::MovedToHeadquarters>(
      std::bind(&StateHandlerOnTheWay::MovedToHeadquartersGameEventHandler, this));

    PrintCli();
}
