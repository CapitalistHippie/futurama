#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_SHIPDAMAGED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_SHIPDAMAGED_H_INCLUDED

namespace fut::domain::events
{
struct ShipDamaged
{
    unsigned int oldDamagePoints = 0;
    unsigned int newDamagePoints = 0;
}; // struct ShipDamaged
} // namespace fut::domain::events

#endif // #ifndef FUTURAMA_FUT_DOMAIN_EVENTS_SHIPDAMAGED_H_INCLUDED
