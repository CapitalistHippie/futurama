#ifndef FUTURAMA_FUT_APP_GAME_H_INCLUDED
#define FUTURAMA_FUT_APP_GAME_H_INCLUDED

#include <fut/dal/encounterrepository.h>
#include <fut/dal/packagerepository.h>
#include <fut/domain/models/character.h>
#include <fut/domain/models/encounter.h>
#include <fut/domain/models/game.h>
#include <fut/infra/point.h>
#include <fut/infra/randomnumbergenerator.h>
#include <fut/infra/subject.h>

#include "fut/app/scangenerator.h"
#include "fut/app/sectorgenerator.h"

namespace fut::app
{
class Game
{
  private:
    domain::models::Game data;

    infra::RandomNumberGenerator* randomNumberGenerator;

    dal::EncounterRepository* encounterRepository;
    dal::PackageRepository* packageRepository;

    ScanGenerator scanGenerator;
    SectorGenerator sectorGenerator;

    void MoveToHeadQuarters();
    void MoveToSector(const infra::Point& sectorPoint, const infra::Point& fieldPoint);
    void MoveToField(const infra::Point& fieldPoint);
    void EnterEncounter();

    infra::Point GetRelativeSectorPoint(const infra::Point& fieldPoint) const;
    infra::Point GetRelativeSectorFieldPoint(const infra::Point& fieldPoint) const;
    void GetFieldsAroundPoint(infra::Point fieldPoint,
                              const domain::models::SectorField** fieldsBuffer,
                              unsigned int& fieldCountBuffer) const;
    void GetFieldsAroundPoint(infra::Point fieldPoint,
                              domain::models::SectorField** fieldsBuffer,
                              unsigned int& fieldCountBuffer);
    void GetScanSectorsAroundPoint(infra::Point sectorPoint,
                                   const domain::models::ScanSector** scanSectorsBuffer,
                                   unsigned int& scanSectorCountBuffer) const;
    const domain::models::SectorField& GetField(const infra::Point& fieldPoint) const;
    domain::models::SectorField& GetField(const infra::Point& fieldPoint);
    const domain::models::ScanSector& GetScanSector(const infra::Point& sectorPoint) const;
    bool IsPointOutsideUniverse(const infra::Point& fieldPoint) const;
    bool IsPointOutsideSector(const infra::Point& fieldPoint) const;

    domain::models::Sector& GetOrGenerateSector(const infra::Point& sectorPoint);
    domain::models::Package GeneratePackage();
    void RemoveEncounter();
    void RemoveEncounterInstance();
    void RemovePackage();
    void RepairShip();
    void DamageShip(unsigned int damage);
    void ChangeVictoryPoints(int points);
    void EndTurn();
    void MoveEncounters();
    void SetState(domain::models::GameState state);

  public:
    infra::Subject eventsSubject;

    Game(infra::RandomNumberGenerator& randomNumberGenerator,
         dal::EncounterRepository& encounterRepository,
         dal::PackageRepository& packageRepository);

    const domain::models::Game& GetData() const noexcept;
    const domain::models::Sector& GetCurrentSector() const;
    bool CanPickupPackage() const;
    bool IsShipNextToThing(domain::models::SectorFieldThing thing) const;
    bool IsShipNextToPackageDestination() const;
    bool HavePackage() const;

    void Reset();
    void MoveToSector(const infra::Point& sectorPoint);
    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void PickupPackage();
    void DeliverPackage();
    void SkipTurn();
    void PickEncounterNegotiator(domain::models::Character negotiator);
}; // class Game
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_GAME_H_INCLUDED
