#ifndef FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
#define FUTURAMA_FUT_APP_CLIENT_H_INCLUDED

#include <fut/dal/encounterfilerepository.h>
#include <fut/dal/packagefilerepository.h>
#include <fut/domain/models/character.h>
#include <fut/infra/point.h>
#include <fut/infra/randomnumbergenerator.h>
#include <fut/infra/subject.h>

#include "fut/app/game.h"
#include "fut/app/gamemanager.h"

namespace fut::app
{
class Client
{
  private:
    infra::RandomNumberGenerator randomNumberGenerator;
    dal::EncounterFileRepository encounterRepository;
    dal::PackageFileRepository packageRepository;

    Game game;

  public:
    infra::Subject eventsSubject;

    Client();

    void ResetGame();
    const Game& GetGame() const;
    infra::Subject& GetGameEventsSubject();

    void MoveToSector(const infra::Point& sectorPoint);
    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
    void PickupPackage();
    void DeliverPackage();
    void SkipTurn();
    void PickEncounterNegotiator(domain::models::Character negotiator);
}; // class Client
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
