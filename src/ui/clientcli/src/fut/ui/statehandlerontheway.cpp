#include "fut/ui/statehandlerontheway.h"

#include <functional>

#include <fut/domain/events/movedtosector.h>
#include <fut/infra/clihelpers.h>

using namespace fut::ui;

void StateHandlerOnTheWay::ExitStateBase() noexcept
{
}

void StateHandlerOnTheWay::MovedToSectorGameEventHandler() const
{
}

void StateHandlerOnTheWay::PrintCli(const char* extra = nullptr) const
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
            if (ship.currentSectorRow == i && ship.currentSectorColumn == ii)
            {
                *outputStream << "P ";

                continue;
            }

            const auto& field = sector.fields[i][ii];

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
    RegisterGameEventObserver<domain::events::MovedToSector>(
      std::bind(&StateHandlerOnTheWay::MovedToSectorGameEventHandler, this));

    PrintCli();
}
