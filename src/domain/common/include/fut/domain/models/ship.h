#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED

#include <fut/infra/point.h>

#include "fut/domain/models/package.h"

namespace fut::domain::models
{
struct Ship
{
    unsigned int damagePoints = 0;
    infra::Point sectorPoint;
    infra::Point fieldPoint;
    Package* package = nullptr;

    ~Ship()
    {
        if (package != nullptr)
        {
            delete package;
        }
    }
}; // struct Ship
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SHIP_H_INCLUDED
