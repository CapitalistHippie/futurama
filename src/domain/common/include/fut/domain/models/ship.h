#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED

#include <fut/infra/point.h>

namespace fut::domain::models
{
struct Ship
{
    unsigned int damagePoints = 0;
    infra::Point sectorPoint;
    infra::Point fieldPoint;
}; // struct Ship
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
