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

void Client::MoveToSector(unsigned int column, unsigned int row)
{
    game.MoveToSector(column, row);
}
