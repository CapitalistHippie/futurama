#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED

namespace fut::domain::models
{
struct Ship
{
    unsigned int damagePoints = 0;
    unsigned int currentSectorColumn;
    unsigned int currentSectorRow;
}; // struct Ship
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
