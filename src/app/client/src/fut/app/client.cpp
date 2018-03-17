#include "fut/app/client.h"

#include <utility>

#include <fut/domain/events/gamestarted.h>

using namespace fut;
using namespace fut::app;

Client::Client(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
  , game(randomNumberGenerator)
{
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
