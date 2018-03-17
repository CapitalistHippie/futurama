#include "fut/app/game.h"

#include <exception>

#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/domain/models/gamestate.h>
#include <fut/infra/point.h>

using namespace fut;
using namespace fut::app;

Game::Game(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
  , scanGenerator(randomNumberGenerator)
  , sectorGenerator(randomNumberGenerator)
  , currentScanColumn(0)
  , currentScanRow(0)
{
    MoveToHeadQuarters();
}

const domain::models::Game& Game::GetData() const noexcept
{
    return data;
}

const domain::models::Sector& fut::app::Game::GetCurrentSector() const
{
    if (data.gameState != domain::models::GameState::OnTheWay)
    {
        throw std::exception("Player is not currently in a sector.");
    }

    return *data.universe.sectors[currentScanColumn][currentScanRow];
}

void Game::MoveToHeadQuarters()
{
    // Reset the universe.
    domain::models::Universe universe;
    data.universe = std::move(universe);

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
        if (row != 0 && row != domain::models::Scan::RowCount - 1)
        {
            throw std::exception("Can only move to a sector on the edge of the scan.");
        }
    }

    const auto& scanSector = data.universe.scan.sectors[column][row];

    domain::models::Sector* sector = nullptr;

    try
    {
        sector = new domain::models::Sector();

        *sector = sectorGenerator.GenerateSector(scanSector);

        data.universe.sectors[column][row] = sector;

        data.gameState = domain::models::GameState::OnTheWay;

        currentScanColumn = column;
        currentScanRow = row;

        // Pick a spot to put the ship.
        constexpr auto fieldCount = domain::models::Sector::ColumnCount * domain::models::Sector::RowCount;

        unsigned int potentialSpotCount = 0;
        infra::Point potentialSpots[fieldCount];

        for (unsigned int i = 0; i < domain::models::Sector::ColumnCount; ++i)
        {
            for (unsigned int ii = 0; ii < domain::models::Sector::RowCount; ++ii)
            {
                if (sector->fields[i][ii].thing != domain::models::SectorFieldThing::Empty)
                {
                    continue;
                }

                potentialSpots[potentialSpotCount].x = i;
                potentialSpots[potentialSpotCount++].y = ii;
            }
        }

        auto index = randomNumberGenerator->GenerateBetweenInclusive(0, potentialSpotCount - 1);

        data.ship.currentSectorColumn = potentialSpots[index].x;
        data.ship.currentSectorRow = potentialSpots[index].y;

        // Throw event.
        domain::events::MovedToSector movedToSectorEvent;
        movedToSectorEvent.scanColumn = column;
        movedToSectorEvent.scanRow = row;
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
