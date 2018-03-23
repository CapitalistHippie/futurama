#include "fut/app/client.h"

#include <utility>

#include <fut/domain/events/gamestarted.h>

using namespace fut;
using namespace fut::app;

Client::Client()
  : meetingRepository(randomNumberGenerator)
  , packageRepository(randomNumberGenerator)
  , game(randomNumberGenerator, packageRepository, meetingRepository)
{
    meetingRepository.ReadMeetingsFromCsv("D:/Projects/futurama/repo/assets/meetings.csv");
    packageRepository.ReadPackagesFromCsv("D:/Projects/futurama/repo/assets/packages.csv");
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
