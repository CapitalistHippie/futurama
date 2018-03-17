#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED

#include "fut/domain/models/sector.h"

namespace fut::domain::events
{
struct MovedToSector
{
    unsigned int scanColumn = 0;
    unsigned int scanRow = 0;

    const models::Sector* sector = nullptr;
}; // struct MovedToSector
} // namespace fut::domain::events

#endif // FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED
