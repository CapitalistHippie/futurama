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
                     "your package on.\n\n";

    PrintSector();

    *outputStream << "\n\n";

    *outputStream << "Available commands.\n"
                  << "sector <column> <row>\t-- Go to this sector.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerOnTheWay::PrintSector() const
{
    const auto& sector = client->GetGame().GetData().universe.scan;

    /**outputStream << "   ";

    for (unsigned int i = 0; i < scan.ColumnCount; ++i)
    {
        *outputStream << ' ' << i << "  ";
    }

    *outputStream << "\n  " << char(218);

    for (unsigned int i = 0; i < scan.ColumnCount - 1; ++i)
    {
        *outputStream << char(196) << char(196) << char(196) << char(196);
    }

    *outputStream << char(196) << char(196) << char(196);

    for (unsigned int i = 0; i < scan.RowCount; ++i)
    {
        *outputStream << "\n " << i << char(179);

        for (unsigned int ii = 0; ii < scan.ColumnCount; ++ii)
        {
            const auto& sector = scan.sectors[ii][i];

            *outputStream << sector.asteroids << sector.meetings << sector.planets << ' ';
        }

        if (i != scan.RowCount - 1)
        {
            *outputStream << "\n  " << char(179);
        }
    }*/
}

void StateHandlerOnTheWay::EnterState()
{
    RegisterGameEventObserver<domain::events::MovedToSector>(
      std::bind(&StateHandlerOnTheWay::MovedToSectorGameEventHandler, this));

    PrintCli();
}
