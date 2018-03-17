#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SECTORFIELD_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SECTORFIELD_H_INCLUDED

#include "fut/domain/models/sectorfieldthing.h"

namespace fut::domain::models
{
struct SectorField
{
    SectorFieldThing thing = SectorFieldThing::Empty;
}; // struct SectorField
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SECTORFIELD_H_INCLUDED
