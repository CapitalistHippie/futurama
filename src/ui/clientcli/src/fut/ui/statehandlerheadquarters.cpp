#include "fut/ui/statehandlerheadquarters.h"

#include <functional>

#include <fut/domain/events/movedtosector.h>
#include <fut/infra/clihelpers.h>
#include <fut/infra/point.h>

#include "fut/ui/statehandlerontheway.h"

using namespace fut::ui;

void StateHandlerHeadquarters::ExitStateBase() noexcept
{
}

void fut::ui::StateHandlerHeadquarters::SectorCommandHandler(const Command& command) const
{
    if (command.argumentCount < 2)
    {
        PrintCli("Too few arguments.");
        return;
    }

    char* endptr;

    infra::Point sectorPoint;

    sectorPoint.x = strtol(command.arguments[0], &endptr, 10);
    if (endptr == command.arguments[0])
    {
        PrintCli("Invalid column index.");
        return;
    }

    if (sectorPoint.x < 0 || sectorPoint.x > domain::models::Scan::ColumnCount - 1)
    {
        PrintCli("Column index out of range.");
        return;
    }

    sectorPoint.y = strtol(command.arguments[1], &endptr, 10);
    if (endptr == command.arguments[1])
    {
        PrintCli("Invalid row index.");
        return;
    }

    if (sectorPoint.y < 0 || sectorPoint.y > domain::models::Scan::RowCount - 1)
    {
        PrintCli("Row index out of range.");
        return;
    }

    if (sectorPoint.x != 0 && sectorPoint.x != domain::models::Scan::ColumnCount - 1)
    {
        if (sectorPoint.y != 0 && sectorPoint.y != domain::models::Scan::RowCount - 1)
        {
            PrintCli("You can only start in a sector on the edge of the scan.");
            return;
        }
    }

    client->MoveToSector(sectorPoint);
}

void StateHandlerHeadquarters::MovedToSectorGameEventHandler() const
{
    context->SetStateHandler<StateHandlerOnTheWay>();
}

void StateHandlerHeadquarters::PrintCli(const char* extra) const
{
    infra::ClearCli();
    *outputStream << "You're in the headquarters. Pick a sector from the scan to start in.\n\n";

    PrintScan();

    *outputStream << "\n\n";

    *outputStream << "Victory points: " << client->GetGame().GetData().player.victoryPoints << '.';

    *outputStream << "\n\n";

    *outputStream << "Available commands.\n"
                  << "sector <column> <row>\t-- Go to this sector.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerHeadquarters::PrintScan() const
{
    const auto& scan = client->GetGame().GetData().universe.scan;

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

    for (unsigned int i = 0; i < scan.RowCount; ++i)
    {
        *outputStream << "\n " << i << char(179);

        for (unsigned int ii = 0; ii < scan.ColumnCount; ++ii)
        {
            const auto& sector = scan.sectors[ii][i];

            *outputStream << sector.asteroids << sector.encounters << sector.planets << ' ';
        }

        if (i != scan.RowCount - 1)
        {
            *outputStream << "\n  " << char(179);
        }
    }
}

void StateHandlerHeadquarters::EnterState()
{
    RegisterCommandObserver("sector",
                            std::bind(&StateHandlerHeadquarters::SectorCommandHandler, this, std::placeholders::_1));

    RegisterGameEventObserver<domain::events::MovedToSector>(
      std::bind(&StateHandlerHeadquarters::MovedToSectorGameEventHandler, this));

    PrintCli();
}
