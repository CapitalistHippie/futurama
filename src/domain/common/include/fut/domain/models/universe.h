#ifndef FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED

#include "fut/domain/models/scan.h"
#include "fut/domain/models/sector.h"

namespace fut::domain::models
{
template<unsigned int sectorColumns,
         unsigned int sectorRows,
         unsigned int sectorFieldColumns,
         unsigned int sectorFieldRows>
struct Universe
{
    Scan<columns, rows> scan;
    Sector<sectorFieldColumns, sectorFieldRows>* sectors[columns][rows];
}; // struct Universe
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
