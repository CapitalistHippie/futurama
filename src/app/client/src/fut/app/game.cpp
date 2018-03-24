#include "fut/app/game.h"

#include <algorithm>
#include <exception>

#include <fut/domain/events/movedtofield.h>
#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/domain/events/packagepickedup.h>
#include <fut/domain/events/statechanged.h>
#include <fut/domain/events/victorypointschanged.h>
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

    RemovePackage();

    // Throw event.
    domain::events::MovedToHeadquarters movedToHeadquartersEvent;
    eventsSubject.NotifyObservers(movedToHeadquartersEvent);
}

void Game::MoveToSector(const infra::Point& sectorPoint, const infra::Point& fieldPoint)
{
    const auto& sector = GetOrGenerateSector(sectorPoint);

    if (sector.fields[fieldPoint.x][fieldPoint.y].thing != domain::models::SectorFieldThing::Empty)
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

    if (currentSector.fields[fieldPoint.x][fieldPoint.y].thing != domain::models::SectorFieldThing::Empty)
    {
        throw FuturamaAppException(ErrorCode::FieldTaken);
    }

    // MoveToField to the point.
    data.ship.fieldPoint = fieldPoint;

    // Throw event.
    domain::events::MovedToField movedToFieldEvent;
    eventsSubject.NotifyObservers(movedToFieldEvent);
}

void fut::app::Game::EnterMeeting()
{
    if (data.gameState != domain::models::GameState::OnTheWay)
    {
        throw std::exception("Player can only move into a meeting while on the way.");
    }

    // SetState(domain::models::GameState::InMeeting);
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

void fut::app::Game::GetScanSectorsAroundPoint(infra::Point sectorPoint,
                                               const domain::models::ScanSector** scanSectorsBuffer,
                                               unsigned int& scanSectorCountBuffer) const
{
    scanSectorCountBuffer = 0;

    sectorPoint.x -= 1;
    sectorPoint.y -= 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.x += 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.x += 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.y += 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.y += 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.x -= 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.x -= 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }

    sectorPoint.y -= 1;
    if (!IsPointOutsideUniverse(sectorPoint))
    {
        scanSectorsBuffer[scanSectorCountBuffer++] = &GetScanSector(sectorPoint);
    }
}

const domain::models::SectorField& Game::GetField(const infra::Point& fieldPoint) const
{
    return data.universe.sectors[data.ship.sectorPoint.x][data.ship.sectorPoint.y]->fields[fieldPoint.x][fieldPoint.y];
}

const domain::models::ScanSector& Game::GetScanSector(const infra::Point& sectorPoint) const
{
    return data.universe.scan.sectors[sectorPoint.x][sectorPoint.y];
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

domain::models::Package fut::app::Game::GeneratePackage()
{
    // Get a random package from the repository.
    auto package = packageRepository->GetRandomPackage();

    // Find an eligible planet to deliver the package to (must be at least two sectors away).
    const domain::models::ScanSector* scanSectorsBuffer[8];
    unsigned int scanSectorCountBuffer;

    GetScanSectorsAroundPoint(data.ship.sectorPoint, scanSectorsBuffer, scanSectorCountBuffer);

    constexpr auto sectorCount = domain::models::Scan::ColumnCount * domain::models::Scan::RowCount;

    unsigned int eligibleScanSectorCount = 0;
    infra::Point eligibleScanSectorPoints[sectorCount];

    for (unsigned int i = 0; i < domain::models::Scan::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Scan::RowCount; ++ii)
        {
            // Check if it's eligible.
            if (std::any_of(scanSectorsBuffer,
                            scanSectorsBuffer + 8,
                            [&](const domain::models::ScanSector* scanSector) {
                                return scanSector == &data.universe.scan.sectors[i][ii];
                            }) ||
                data.universe.scan.sectors[i][ii].planets == 0)
            {
                continue;
            }

            eligibleScanSectorPoints[eligibleScanSectorCount].x = i;
            eligibleScanSectorPoints[eligibleScanSectorCount++].y = ii;
        }
    }

    if (eligibleScanSectorCount == 0)
    {
        throw std::exception("No eligible planets found to deliver a package to.");
    }

    const auto& sectorPoint =
      eligibleScanSectorPoints[randomNumberGenerator->GenerateBetweenInclusive(0, eligibleScanSectorCount - 1)];

    package.destinationSectorPoint = sectorPoint;

    const auto& sector = GetOrGenerateSector(sectorPoint);

    auto planetIndex = randomNumberGenerator->GenerateBetweenInclusive(
      1, data.universe.scan.sectors[sectorPoint.x][sectorPoint.y].planets);

    for (unsigned int i = 0; i < domain::models::Sector::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Sector::RowCount; ++ii)
        {
            if (sector.fields[i][ii].thing == domain::models::SectorFieldThing::Planet)
            {
                if (--planetIndex != 0)
                {
                    continue;
                }

                package.destinationFieldPoint.x = i;
                package.destinationFieldPoint.y = ii;
            }
        }
    }

    return package;
}

domain::models::Meeting Game::GenerateMeeting()
{
    return domain::models::Meeting();
}

void Game::RemovePackage()
{
    if (!HavePackage())
    {
        return;
    }

    delete data.ship.package;
    data.ship.package = nullptr;
}

void Game::ChangeVictoryPoints(int points)
{
    unsigned int oldPoints = data.player.victoryPoints;

    data.player.victoryPoints += points;

    if (data.player.victoryPoints < 0)
    {
        data.player.victoryPoints = 0;
    }

    if (oldPoints == data.player.victoryPoints)
    {
        return;
    }

    // Throw event.
    domain::events::VictoryPointsChanged victoryPointsChangedEvent;
    victoryPointsChangedEvent.oldPoints = oldPoints;
    victoryPointsChangedEvent.newPoints = data.player.victoryPoints;
    eventsSubject.NotifyObservers(victoryPointsChangedEvent);

    if (data.player.victoryPoints >= 10)
    {
        SetState(domain::models::GameState::Win);
    }
}

void Game::EndTurn()
{
    // Check if last turn didn't change the state.
    if (data.gameState != domain::models::GameState::OnTheWay)
    {
        return;
    }

    MoveMeetings();

    if (IsShipNextToThing(domain::models::SectorFieldThing::Meeting))
    {
        EnterMeeting();
    }
}

void Game::MoveMeetings()
{
    if (data.gameState != domain::models::GameState::OnTheWay)
    {
        throw std::exception("Can only move meetings while on the way.");
    }

    auto& sector = GetOrGenerateSector(data.ship.sectorPoint);
    const auto& shipFieldPoint = data.ship.fieldPoint;

    unsigned int meetingCount = 0;
    infra::Point meetingFieldPoints[3];

    for (int i = 0; i < domain::models::Sector::ColumnCount; ++i)
    {
        for (int ii = 0; ii < domain::models::Sector::RowCount; ++ii)
        {
            if (sector.fields[i][ii].thing == domain::models::SectorFieldThing::Meeting)
            {
                meetingFieldPoints[meetingCount++] = infra::Point(i, ii);
            }
        }
    }

    for (unsigned int i = 0; i < meetingCount; ++i)
    {
        if (infra::IsPointNextToPoint(meetingFieldPoints[i], shipFieldPoint))
        {
            continue;
        }

        auto x = meetingFieldPoints[i].x;
        auto y = meetingFieldPoints[i].y;

        if (x < data.ship.fieldPoint.x && sector.fields[x + 1][y].thing == domain::models::SectorFieldThing::Empty)
        {
            sector.fields[x + 1][y].thing = domain::models::SectorFieldThing::Meeting;
            sector.fields[x][y].thing = domain::models::SectorFieldThing::Empty;
        }
        else if (x > data.ship.fieldPoint.x && sector.fields[x - 1][y].thing == domain::models::SectorFieldThing::Empty)
        {
            sector.fields[x - 1][y].thing = domain::models::SectorFieldThing::Meeting;
            sector.fields[x][y].thing = domain::models::SectorFieldThing::Empty;
        }
        else if (y < data.ship.fieldPoint.y && sector.fields[x][y + 1].thing == domain::models::SectorFieldThing::Empty)
        {
            sector.fields[x][y + 1].thing = domain::models::SectorFieldThing::Meeting;
            sector.fields[x][y].thing = domain::models::SectorFieldThing::Empty;
        }
        else if (y > data.ship.fieldPoint.y && sector.fields[x][y - 1].thing == domain::models::SectorFieldThing::Empty)
        {
            sector.fields[x][y - 1].thing = domain::models::SectorFieldThing::Meeting;
            sector.fields[x][y].thing = domain::models::SectorFieldThing::Empty;
        }
    }
}

void Game::SetState(domain::models::GameState state)
{
    domain::events::StateChanged evt;
    evt.oldState = data.gameState;
    evt.newState = state;

    data.gameState = state;

    eventsSubject.NotifyObservers(evt);
}

Game::Game(infra::RandomNumberGenerator& randomNumberGenerator,
           dal::PackageRepository& packageRepository,
           dal::MeetingRepository& meetingRepository)
  : randomNumberGenerator(&randomNumberGenerator)
  , packageRepository(&packageRepository)
  , meetingRepository(&meetingRepository)
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

    // Check if there's a planet around the player to pickup a package from.
    if (!IsShipNextToThing(domain::models::SectorFieldThing::Planet))
    {
        return false;
    }

    // Check if there's an eligible planet to deliver the package to (must be at least two sectors away).
    const domain::models::ScanSector* scanSectorsBuffer[8];
    unsigned int scanSectorCountBuffer;

    GetScanSectorsAroundPoint(data.ship.sectorPoint, scanSectorsBuffer, scanSectorCountBuffer);

    unsigned int eligibleScanSectorCount = 0;

    for (unsigned int i = 0; i < domain::models::Scan::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Scan::RowCount; ++ii)
        {
            // Check if it's eligible.
            if (std::any_of(scanSectorsBuffer,
                            scanSectorsBuffer + 8,
                            [&](const domain::models::ScanSector* scanSector) {
                                return scanSector == &data.universe.scan.sectors[i][ii];
                            }) ||
                data.universe.scan.sectors[i][ii].planets == 0)
            {
                continue;
            }

            eligibleScanSectorCount++;
        }
    }

    if (eligibleScanSectorCount == 0)
    {
        return false;
    }

    return true;
}

bool Game::IsShipNextToThing(domain::models::SectorFieldThing thing) const
{
    const domain::models::SectorField* fieldsBuffer[8];
    unsigned int fieldCountBuffer;

    GetFieldsAroundPoint(data.ship.fieldPoint, fieldsBuffer, fieldCountBuffer);

    unsigned int thingAroundPlayerCount = 0;

    for (unsigned int i = 0; i < fieldCountBuffer; ++i)
    {
        const domain::models::SectorField& field = *fieldsBuffer[i];

        if (field.thing == thing)
        {
            thingAroundPlayerCount++;
        }
    }

    return thingAroundPlayerCount != 0;
}

bool Game::IsShipNextToPackageDestination() const
{
    if (!HavePackage())
    {
        throw std::exception("Player doesn't have a package.");
    }

    const domain::models::Ship& ship = data.ship;

    return ship.sectorPoint == ship.package->destinationSectorPoint &&
           infra::IsPointNextToPoint(ship.fieldPoint, ship.package->destinationFieldPoint);
}

bool Game::HavePackage() const
{
    return data.ship.package != nullptr;
}

void Game::Reset()
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

    data.ship.damagePoints = 0;
    data.player.victoryPoints = 0;
    data.gameState = domain::models::GameState::Headquarters;

    RemovePackage();
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
            if (sector.fields[i][ii].thing != domain::models::SectorFieldThing::Empty)
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

    EndTurn();
}

void Game::MoveRight()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.x += 1;

    MoveToField(fieldPoint);

    EndTurn();
}

void Game::MoveDown()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.y += 1;

    MoveToField(fieldPoint);

    EndTurn();
}

void Game::MoveLeft()
{
    infra::Point fieldPoint = data.ship.fieldPoint;
    fieldPoint.x -= 1;

    MoveToField(fieldPoint);

    EndTurn();
}

void Game::PickupPackage()
{
    if (HavePackage())
    {
        throw std::exception("Can not pick up a package while there is an active package to deliver.");
    }

    auto package = GeneratePackage();
    data.ship.package = new domain::models::Package(std::move(package));

    // Throw event.
    domain::events::PackagePickedUp packagePickedUpEvent;
    eventsSubject.NotifyObservers(packagePickedUpEvent);

    EndTurn();
}

void Game::DeliverPackage()
{
    if (!IsShipNextToPackageDestination())
    {
        throw std::exception("Player is not next to the package destination.");
    }

    MoveToHeadQuarters();

    ChangeVictoryPoints(1);
}

void Game::SkipTurn()
{
    EndTurn();
}
