#ifndef FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED

#include "fut/domain/models/player.h"
#include "fut/domain/models/ship.h"
#include "fut/domain/models/universe.h"

namespace fut::domain::models
{
struct Game
{
    Player player;
    Ship ship;
    Universe<5, 5, 10, 10> universe;
}; // struct Game
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_GAME_H_INCLUDED
