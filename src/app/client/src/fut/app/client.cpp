#include "fut/app/client.h"

#include <utility>

#include <fut/domain/events/gamestarted.h>

using namespace fut;
using namespace fut::app;

Client::Client(infra::RandomNumberGenerator& randomNumberGenerator)
  : scanGenerator(randomNumberGenerator)
  , isGameRunning(false)
{
}

void Client::StartGame()
{
    if (IsGameRunning())
    {
        return;
    }

    isGameRunning = true;

    // Easy previous game cleanup.
    domain::models::Game newGame;
    game = std::move(newGame);

    // Initialize the game.
    game.universe.scan = scanGenerator.GenerateScan();

    // Throw game started event.
    domain::events::GameStarted gameStartedEvent;
    eventsSubject.NotifyObservers(gameStartedEvent);
}

void Client::StopGame()
{
    if (!IsGameRunning())
    {
        return;
    }

    isGameRunning = false;
}

bool Client::IsGameRunning() const
{
    return isGameRunning;
}

const domain::models::Game& Client::GetGame() const
{
    return game;
}
