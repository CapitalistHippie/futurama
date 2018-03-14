#ifndef FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
#define FUTURAMA_FUT_APP_CLIENT_H_INCLUDED

#include <fut/domain/models/game.h>
#include <fut/infra/randomnumbergenerator.h>

#include "fut/app/scangenerator.h"

namespace fut::app
{
class Client
{
  private:
    domain::models::Game game;

    ScanGenerator scanGenerator;

    bool isGameRunning;

  public:
    Client(infra::RandomNumberGenerator& randomNumberGenerator);

    void StartGame();
    void StopGame();

    bool IsGameRunning() const;

    const domain::models::Game& GetGame() const;
}; // class Client
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_CLIENT_H_INCLUDED
