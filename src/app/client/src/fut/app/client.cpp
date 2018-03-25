#include "fut/app/client.h"

#include <utility>

#include <fut/domain/events/gamestarted.h>

using namespace fut;
using namespace fut::app;

Client::Client()
  : encounterRepository(randomNumberGenerator)
  , packageRepository(randomNumberGenerator)
  , game(randomNumberGenerator, encounterRepository, packageRepository)
{
    encounterRepository.ReadEncountersFromCsv("D:/Projects/futurama/repo/assets/encounters.csv");
    packageRepository.ReadPackagesFromCsv("D:/Projects/futurama/repo/assets/packages.csv");
}

void Client::ResetGame()
{
    game.Reset();
}

const Game& Client::GetGame() const
{
    return game;
}

infra::Subject& Client::GetGameEventsSubject()
{
    return game.eventsSubject;
}

void Client::MoveToSector(const infra::Point& sectorPoint)
{
    game.MoveToSector(sectorPoint);
}

void Client::MoveUp()
{
    game.MoveUp();
}

void Client::MoveRight()
{
    game.MoveRight();
}

void Client::MoveDown()
{
    game.MoveDown();
}

void Client::MoveLeft()
{
    game.MoveLeft();
}

void Client::PickupPackage()
{
    game.PickupPackage();
}

void Client::DeliverPackage()
{
    game.DeliverPackage();
}

void Client::SkipTurn()
{
    game.SkipTurn();
}

void Client::PickEncounterNegotiator(domain::models::Character negotiator)
{
    game.PickEncounterNegotiator(negotiator);
}
