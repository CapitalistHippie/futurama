#ifndef FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED

#include "fut/domain/models/gamestate.h"
#include "fut/domain/models/meeting.h"
#include "fut/domain/models/player.h"
#include "fut/domain/models/ship.h"
#include "fut/domain/models/universe.h"

namespace fut::domain::models
{
struct Game
{
    GameState gameState = GameState::Headquarters;
    Player player;
    Ship ship;
    Universe universe;
    Meeting* meeting = nullptr;

    ~Game()
    {
        if (meeting != nullptr)
        {
            delete meeting;
        }
    }
}; // struct Game
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED
