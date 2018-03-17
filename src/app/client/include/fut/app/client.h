#ifndef FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
#define FUTURAMA_FUT_APP_CLIENT_H_INCLUDED

#include <fut/infra/randomnumbergenerator.h>
#include <fut/infra/subject.h>

#include "fut/app/game.h"
#include "fut/app/gamemanager.h"

namespace fut::app
{
class Client
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

    Game game;

  public:
    infra::Subject eventsSubject;

    Client(infra::RandomNumberGenerator& randomNumberGenerator);

    const Game& GetGame() const;
    infra::Subject& GetGameEventsSubject();

    void MoveToSector(unsigned int column, unsigned int row);
}; // class Client
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
