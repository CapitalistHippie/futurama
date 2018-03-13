#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED

#include "fut/domain/models/sectorfield.h"

namespace fut::domain::models
{
template<unsigned int columns, unsigned int rows>
struct Sector
{
    SectorField fields[columns][rows];
}; // struct Sector
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
