#ifndef FUTURAMA_FUT_APP_GAME_H_INCLUDED
#define FUTURAMA_FUT_APP_GAME_H_INCLUDED

#include <fut/domain/models/game.h>
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

    ScanGenerator scanGenerator;
    SectorGenerator sectorGenerator;

  public:
    infra::Subject eventsSubject;

    Game(infra::RandomNumberGenerator& randomNumberGenerator);

    const domain::models::Game& GetData() const noexcept;

    void MoveToHeadQuarters();
    void MoveToSector(unsigned int column, unsigned int row);
}; // class Game
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_GAME_H_INCLUDED
