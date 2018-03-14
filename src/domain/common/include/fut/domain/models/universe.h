#ifndef FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED

#include "fut/domain/models/scan.h"
#include "fut/domain/models/sector.h"

namespace fut::domain::models
{
struct Universe
{
    Scan scan;
    Sector* sectors[5][5];
}; // struct Universe
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
