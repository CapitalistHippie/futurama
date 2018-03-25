#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_SHIPREPAIRED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_SHIPREPAIRED_H_INCLUDED

namespace fut::domain::events
{
struct ShipRepaired
{
    unsigned int oldDamagePoints = 0;
}; // struct ShipRepaired
} // namespace fut::domain::events

#endif // #ifndef FUTURAMA_FUT_DOMAIN_EVENTS_SHIPREPAIRED_H_INCLUDED
