#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED

#include "fut/domain/models/sectorfield.h"

namespace fut::domain::models
{
struct Sector
{
    SectorField fields[10][10];
}; // struct Sector
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
