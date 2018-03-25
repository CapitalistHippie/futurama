#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_ENCOUNTERSTARTED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_ENCOUNTERSTARTED_H_INCLUDED

#include "fut/domain/models/encounterinstance.h"

namespace fut::domain::events
{
struct EncounterStarted
{
    const models::EncounterInstance* encounter;
}; // struct EncounterStarted
} // namespace fut::domain::events

#endif // #ifndef FUTURAMA_FUT_DOMAIN_EVENTS_ENCOUNTERSTARTED_H_INCLUDED
