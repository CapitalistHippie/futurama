#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_STATECHANGED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_STATECHANGED_H_INCLUDED

#include "fut/domain/models/gamestate.h"

namespace fut::domain::events
{
struct StateChanged
{
    models::GameState oldState;
    models::GameState newState;
}; // struct StateChanged
} // namespace fut::domain::events

#endif // FUTURAMA_FUT_DOMAIN_EVENTS_STATECHANGED_H_INCLUDED
