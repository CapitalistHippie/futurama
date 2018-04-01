#ifndef FUTURAMA_FUT_DOMAIN_EVENTS_ENEMYMISSED_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_EVENTS_ENEMYMISSED_H_INCLUDED

namespace fut::domain::events
{
struct EnemyMissed
{
    unsigned int enemyHitCount = 0;
}; // struct EnemyMissed
} // namespace fut::domain::events

#endif // #ifndef FUTURAMA_FUT_DOMAIN_EVENTS_ENEMYMISSED_H_INCLUDED
