#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED

#include <fut/infra/point.h>

#include "fut/domain/models/sector.h"

namespace fut::domain::events
{
struct MovedToSector
{
    infra::Point sectorPoint;

    const models::Sector* sector = nullptr;
}; // struct MovedToSector
} // namespace fut::domain::events

#endif // FUTURAMA_FUT_DOMAIN_EVENTS_MOVEDTOSECTOR_H_INCLUDED
