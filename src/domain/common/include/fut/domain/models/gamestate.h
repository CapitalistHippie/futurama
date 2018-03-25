#ifndef FUTURAMA_FUT_DOMAIN_MODELS_GAMESTATE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_GAMESTATE_H_INCLUDED

namespace fut::domain::models
{
enum class GameState
{
    Headquarters,
    OnTheWay,
    PickingEncounterNegotiator,
    Win,
    Lose
}; // enum class GameState
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_GAMESTATE_H_INCLUDED
