#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED

#include "fut/domain/models/sectorfield.h"

namespace fut::domain::models
{
struct Sector
{
    static const unsigned int ColumnCount = 10;
    static const unsigned int RowCount = 10;

    SectorField fields[ColumnCount][RowCount];
}; // struct Sector
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SECTOR_H_INCLUDED
