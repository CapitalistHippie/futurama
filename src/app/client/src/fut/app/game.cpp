#include "fut/app/game.h"

#include <exception>

#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/domain/models/gamestate.h>

using namespace fut;
using namespace fut::app;

Game::Game(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
  , scanGenerator(randomNumberGenerator)
  , sectorGenerator(randomNumberGenerator)
{
    MoveToHeadQuarters();
}

const domain::models::Game& Game::GetData() const noexcept
{
    return data;
}

void Game::MoveToHeadQuarters()
{
    data.universe.scan = scanGenerator.GenerateScan();
    data.ship.damagePoints = 0;
    data.gameState = domain::models::GameState::Headquarters;

    // Throw event.
    domain::events::MovedToHeadquarters movedToHeadquartersEvent;
    eventsSubject.NotifyObservers(movedToHeadquartersEvent);
}

void Game::MoveToSector(unsigned int column, unsigned int row)
{
    if (column != 0 && column != domain::models::Scan::ColumnCount - 1)
    {
        throw std::exception("Can only move to a sector on the edge of the scan.");
    }

    if (row != 0 && row != domain::models::Scan::RowCount - 1)
    {
        throw std::exception("Can only move to a sector on the edge of the scan.");
    }

    const auto& scanSector = data.universe.scan.sectors[column][row];

    domain::models::Sector* sector = nullptr;

    try
    {
        sector = new domain::models::Sector();

        *sector = sectorGenerator.GenerateSector(scanSector);

        data.universe.sectors[column][row] = sector;

        data.gameState = domain::models::GameState::OnTheWay;

        // Throw event.
        domain::events::MovedToSector movedToSectorEvent;
        movedToSectorEvent.sectorColumn = column;
        movedToSectorEvent.sectorRow = row;
        movedToSectorEvent.sector = sector;
        eventsSubject.NotifyObservers(movedToSectorEvent);
    }
    catch (...)
    {
        data.universe.sectors[column][row] = nullptr;

        if (sector != nullptr)
        {
            delete sector;
        }

        throw;
    }
}
