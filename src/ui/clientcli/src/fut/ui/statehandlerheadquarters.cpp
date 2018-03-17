#include "fut/ui/statehandlerheadquarters.h"

#include <functional>

#include <fut/domain/events/movedtosector.h>
#include <fut/infra/clihelpers.h>

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

    auto column = strtol(command.arguments[0], &endptr, 10);
    if (endptr == command.arguments[0])
    {
        PrintCli("Invalid column index.");
        return;
    }

    if (column < 0 || column > domain::models::Scan::ColumnCount - 1)
    {
        PrintCli("Column index out of range.");
        return;
    }

    if (column != 0 && column != domain::models::Scan::ColumnCount - 1)
    {
        PrintCli("You can only start in a sector on the edge of the scan.");
        return;
    }

    auto row = strtol(command.arguments[1], &endptr, 10);
    if (endptr == command.arguments[1])
    {
        PrintCli("Invalid row index.");
        return;
    }

    if (row < 0 || row > domain::models::Scan::RowCount - 1)
    {
        PrintCli("Row index out of range.");
        return;
    }

    if (row != 0 && row != domain::models::Scan::RowCount - 1)
    {
        PrintCli("You can only start in a sector on the edge of the scan.");
        return;
    }

    client->MoveToSector(column, row);
}

void StateHandlerHeadquarters::MovedToSectorGameEventHandler() const
{
    context->SetStateHandler<StateHandlerOnTheWay>();
}

void StateHandlerHeadquarters::PrintCli(const char* extra = nullptr) const
{
    infra::ClearCli();
    *outputStream << "You're in the headquarters. Pick a sector from the scan to start in.\n\n";

    PrintScan();

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

            *outputStream << sector.asteroids << sector.meetings << sector.planets << ' ';
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
