#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_VICTORYPOINTSCHANGED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_VICTORYPOINTSCHANGED_H_INCLUDED

namespace fut::domain::events
{
struct VictoryPointsChanged
{
    unsigned int oldPoints;
    unsigned int newPoints;
}; // struct VictoryPointsChanged
} // namespace fut::domain::events

#endif // FUTURAMA_FUT_DOMAIN_EVENTS_VICTORYPOINTSCHANGED_H_INCLUDED
