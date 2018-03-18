#include "fut/app/game.h"

#include <exception>

#include <fut/domain/events/movedtofield.h>
#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/domain/models/gamestate.h>
#include <fut/infra/point.h>

#include "fut/app/errorcode.h"
#include "fut/app/futuramaappexception.h"

using namespace fut;
using namespace fut::app;

void Game::MoveToHeadQuarters()
{
    // Reset the universe.
    for (unsigned int i = 0; i < domain::models::Scan::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Scan::RowCount; ++ii)
        {
            if (data.universe.sectors[i][ii] != nullptr)
            {
                delete data.universe.sectors[i][ii];
                data.universe.sectors[i][ii] = nullptr;
            }
        }
    }

    data.universe.scan = scanGenerator.GenerateScan();
    data.ship.damagePoints = 0;
    data.gameState = domain::models::GameState::Headquarters;

    // Throw event.
    domain::events::MovedToHeadquarters movedToHeadquartersEvent;
    eventsSubject.NotifyObservers(movedToHeadquartersEvent);
}

void Game::MoveToSector(const infra::Point& sectorPoint, const infra::Point& fieldPoint)
{
    const auto& sector = GetOrGenerateSector(sectorPoint);

    if (sector.columns[fieldPoint.x][fieldPoint.y].thing != domain::models::SectorFieldThing::Empty)
    {
        throw FuturamaAppException(ErrorCode::FieldTaken);
    }

    data.gameState = domain::models::GameState::OnTheWay;
    data.ship.sectorPoint = sectorPoint;
    data.ship.fieldPoint = fieldPoint;

    domain::events::MovedToSector movedToSectorEvent;
    movedToSectorEvent.sectorPoint = sectorPoint;
    movedToSectorEvent.sector = &sector;
    eventsSubject.NotifyObservers(movedToSectorEvent);
}

void Game::MoveToField(const infra::Point& fieldPoint)
{
    if (data.gameState != domain::models::GameState::OnTheWay)
    {
        throw std::exception("Player is not currently in a sector.");
    }

    // If the point we're going to is outside of the universe we go back to HQ.
    if (IsPointOutsideUniverse(fieldPoint))
    {
        MoveToHeadQuarters();
        return;
    }

    // Else if the point is in another sector. We move to that sector.
    auto sectorPoint = GetRelativeSectorPoint(fieldPoint);
    if (sectorPoint != data.ship.sectorPoint)
    {
        auto sectorFieldPoint = GetRelativeSectorFieldPoint(fieldPoint);

        MoveToSector(sectorPoint, sectorFieldPoint);

        return;
    }

    // Check if the field isn't taken by something else.
    const auto& currentSector = GetCurrentSector();

    if (currentSector.columns[fieldPoint.x][fieldPoint.y].thing != domain::models::SectorFieldThing::Empty)
    {
        throw FuturamaAppException(ErrorCode::FieldTaken);
    }

    // MoveToField to the point.
    data.ship.fieldPoint = fieldPoint;

    // Throw event.
    domain::events::MovedToField movedToFieldEvent;
    eventsSubject.NotifyObservers(movedToFieldEvent);
}

infra::Point fut::app::Game::GetRelativeSectorPoint(const infra::Point& fieldPoint) const
{
    infra::Point sectorPoint = data.ship.sectorPoint;

    if (fieldPoint.x < 0)
    {
        sectorPoint.x--;
    }
    else if (fieldPoint.x >= domain::models::Sector::ColumnCount)
    {
        sectorPoint.x++;
    }

    if (fieldPoint.y < 0)
    {
        sectorPoint.y--;
    }
    else if (fieldPoint.y >= domain::models::Sector::RowCount)
    {
        sectorPoint.y++;
    }

    return sectorPoint;
}

infra::Point fut::app::Game::GetRelativeSectorFieldPoint(const infra::Point& fieldPoint) const
{
    infra::Point sectorFieldPoint = fieldPoint;

    if (fieldPoint.x < 0)
    {
        sectorFieldPoint.x = domain::models::Sector::ColumnCount - 1;
    }
    else if (fieldPoint.x >= domain::models::Sector::ColumnCount)
    {
        sectorFieldPoint.x = 0;
    }

    if (fieldPoint.y < 0)
    {
        sectorFieldPoint.y = domain::models::Sector::RowCount - 1;
    }
    else if (fieldPoint.y >= domain::models::Sector::RowCount)
    {
        sectorFieldPoint.y = 0;
    }

    return sectorFieldPoint;
}

void Game::GetFieldsAroundPoint(infra::Point fieldPoint,
                                const domain::models::SectorField** fieldsBuffer,
                                unsigned int& fieldCountBuffer) const
{
    fieldCountBuffer = 0;

    fieldPoint.x -= 1;
    fieldPoint.y -= 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.x += 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.x += 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.y += 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.y += 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.x -= 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.x -= 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }

    fieldPoint.y -= 1;
    if (!IsPointOutsideSector(fieldPoint))
    {
        fieldsBuffer[fieldCountBuffer++] = &GetField(fieldPoint);
    }
}

const domain::models::SectorField& Game::GetField(const infra::Point& fieldPoint) const
{
    return data.universe.sectors[data.ship.sectorPoint.x][data.ship.sectorPoint.y]->columns[fieldPoint.x][fieldPoint.y];
}

bool Game::IsPointOutsideUniverse(const infra::Point& fieldPoint) const
{
    if (fieldPoint.x < 0 && data.ship.sectorPoint.x == 0)
    {
        return true;
    }
    else if (fieldPoint.x >= domain::models::Sector::ColumnCount &&
             data.ship.sectorPoint.x == domain::models::Scan::ColumnCount - 1)
    {
        return true;
    }
    else if (fieldPoint.y < 0 && data.ship.sectorPoint.y == 0)
    {
        return true;
    }
    else if (fieldPoint.y >= domain::models::Sector::RowCount &&
             data.ship.sectorPoint.y == domain::models::Scan::RowCount - 1)
    {
        return true;
    }

    return false;
}

bool Game::IsPointOutsideSector(const infra::Point& fieldPoint) const
{
    if (fieldPoint.x < 0 || fieldPoint.x >= domain::models::Sector::ColumnCount || fieldPoint.y < 0 ||
        fieldPoint.y >= domain::models::Sector::RowCount)
    {
        return true;
    }

    return false;
}

domain::models::Sector& Game::GetOrGenerateSector(const infra::Point& sectorPoint)
{
    domain::models::Sector* sector = data.universe.sectors[sectorPoint.x][sectorPoint.y];

    if (sector != nullptr)
    {
        return *sector;
    }

    const auto& scanSector = data.universe.scan.sectors[sectorPoint.x][sectorPoint.y];

    try
    {
        sector = new domain::models::Sector();

        *sector = sectorGenerator.GenerateSector(scanSector);

        data.universe.sectors[sectorPoint.x][sectorPoint.y] = sector;

        return *sector;
    }
    catch (...)
    {
        data.universe.sectors[sectorPoint.x][sectorPoint.y] = nullptr;

        if (sector != nullptr)
        {
            delete sector;
        }

        throw;
    }
}

Game::Game(infra::RandomNumberGenerator& randomNumberGenerator, dal::PackageRepository& packageRepository)
  : randomNumberGenerator(&randomNumberGenerator)
  , packageRepository(&packageRepository)
  , scanGenerator(randomNumberGenerator)
  , sectorGenerator(randomNumberGenerator)
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

    return *data.universe.sectors[data.ship.sectorPoint.x][data.ship.sectorPoint.y];
}

bool Game::CanPickupPackage() const
{
    if (HavePackage())
    {
        return false;
    }

    const domain::models::SectorField* fieldsBuffer[8];
    unsigned int fieldCountBuffer;

    GetFieldsAroundPoint(data.ship.fieldPoint, fieldsBuffer, fieldCountBuffer);

    for (unsigned int i = 0; i < fieldCountBuffer; ++i)
    {
        const domain::models::SectorField& field = *fieldsBuffer[i];

        if (field.thing == domain::models::SectorFieldThing::Planet)
        {
            return true;
        }
    }

    return false;
}

bool Game::HavePackage() const
{
    return data.ship.package != nullptr;
}

void Game::MoveToSector(const infra::Point& sectorPoint)
{
    if (data.gameState != domain::models::GameState::Headquarters)
    {
        throw std::exception("Moving to a specific sector is only allowed while in headquarters.");
    }

    if (sectorPoint.x != 0 && sectorPoint.x != domain::models::Scan::ColumnCount - 1)
    {
        if (sectorPoint.y != 0 && sectorPoint.y != domain::models::Scan::RowCount - 1)
        {
            throw std::exception("Can only move to a sector on the edge of the universe.");
        }
    }

    domain::models::Sector& sector = GetOrGenerateSector(sectorPoint);

    // Pick a spot to put the ship.
    constexpr auto columnCount = domain::models::Sector::ColumnCount * domain::models::Sector::RowCount;

    unsigned int potentialSpotCount = 0;
    infra::Point potentialSpots[columnCount];

    for (unsigned int i = 0; i < domain::models::Sector::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Sector::RowCount; ++ii)
        {
            if (sector.columns[i][ii].thing != domain::models::SectorFieldThing::Empty)
            {
                continue;
            }

            potentialSpots[potentialSpotCount].x = i;
            potentialSpots[potentialSpotCount++].y = ii;
        }
    }

    auto index = randomNumberGenerator->GenerateBetweenInclusive(0, potentialSpotCount - 1);

    MoveToSector(sectorPoint, potentialSpots[index]);
}

void Game::MoveUp()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.y -= 1;

    MoveToField(fieldPoint);
}

void Game::MoveRight()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.x += 1;

    MoveToField(fieldPoint);
}

void Game::MoveDown()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.y += 1;

    MoveToField(fieldPoint);
}

void Game::MoveLeft()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.x -= 1;

    MoveToField(fieldPoint);
}

void Game::PickupPackage()
{
    if (HavePackage())
    {
        throw std::exception("Can not pick up a package while there is an active package to deliver.");
    }

    const domain::models::SectorField* fieldsBuffer[8];
    unsigned int fieldCountBuffer;

    GetFieldsAroundPoint(data.ship.fieldPoint, fieldsBuffer, fieldCountBuffer);
}
