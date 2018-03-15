#include "fut/ui/statehandlerheadquarters.h"

#include <functional>

#include <fut/infra/clihelpers.h>

using namespace fut::ui;

void StateHandlerHeadquarters::ExitStateBase() noexcept
{
}

void StateHandlerHeadquarters::PrintScan() const
{
    const auto& scan = client->GetGame().universe.scan;

    *outputStream << "   ";

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

    for (unsigned int i = 0; i < scan.ColumnCount; ++i)
    {
        *outputStream << "\n " << i << char(179);

        for (unsigned int ii = 0; ii < scan.RowCount; ++ii)
        {
            const auto& sector = scan.sectors[ii][i];

            *outputStream << sector.asteroids << sector.meetings << sector.planets << ' ';
        }

        if (i != scan.ColumnCount - 1)
        {
            *outputStream << "\n  " << char(179);
        }
    }

    *outputStream << "\n\n";
}

void StateHandlerHeadquarters::EnterState()
{
    infra::ClearCli();
    *outputStream << "You're in the headquarters. Pick a sector from the scan to start in.\n\n";

    PrintScan();
}
