#ifndef FUTURAMA_FUT_APP_GAME_H_INCLUDED
#define FUTURAMA_FUT_APP_GAME_H_INCLUDED

#include <fut/dal/packagerepository.h>
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

    dal::PackageRepository* packageRepository;

    ScanGenerator scanGenerator;
    SectorGenerator sectorGenerator;

    void MoveToHeadQuarters();
    void MoveToSector(const infra::Point& sectorPoint, const infra::Point& fieldPoint);
    void MoveToField(const infra::Point& fieldPoint);

    infra::Point GetRelativeSectorPoint(const infra::Point& fieldPoint) const;
    infra::Point GetRelativeSectorFieldPoint(const infra::Point& fieldPoint) const;
    void GetFieldsAroundPoint(infra::Point fieldPoint,
                              const domain::models::SectorField** fieldsBuffer,
                              unsigned int& fieldCountBuffer) const;
    const domain::models::SectorField& GetField(const infra::Point& fieldPoint) const;
    bool IsPointOutsideUniverse(const infra::Point& fieldPoint) const;
    bool IsPointOutsideSector(const infra::Point& fieldPoint) const;

    domain::models::Sector& GetOrGenerateSector(const infra::Point& sectorPoint);

  public:
    infra::Subject eventsSubject;

    Game(infra::RandomNumberGenerator& randomNumberGenerator, dal::PackageRepository& packageRepository);

    const domain::models::Game& GetData() const noexcept;
    const domain::models::Sector& GetCurrentSector() const;
    bool CanPickupPackage() const;
    bool HavePackage() const;

    void MoveToSector(const infra::Point& sectorPoint);
    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void PickupPackage();
}; // class Game
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_GAME_H_INCLUDED
