#include "fut/app/sectorgenerator.h"

using namespace fut;
using namespace fut::app;

SectorGenerator::SectorGenerator(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
{
}

domain::models::Sector SectorGenerator::GenerateSector(const domain::models::ScanSector& scanSector) const
{
    domain::models::Sector sector;

    constexpr auto columnCount = domain::models::Sector::ColumnCount * domain::models::Sector::RowCount;

    unsigned int sectorFieldThingsIndex = 0;
    domain::models::SectorFieldThing* sectorFieldThings[columnCount];

    for (unsigned int i = 0; i < domain::models::Sector::ColumnCount; ++i)
    {
        for (unsigned int ii = 0; ii < domain::models::Sector::RowCount; ++ii)
        {
            sectorFieldThings[sectorFieldThingsIndex++] = &sector.fields[i][ii].thing;
        }
    }

    unsigned int usedFieldsCount = 0;

    for (unsigned int i = 0; i < scanSector.asteroids; ++i)
    {
        auto index = randomNumberGenerator->GenerateBetweenInclusive(0, columnCount - usedFieldsCount - 1);

        *sectorFieldThings[index] = domain::models::SectorFieldThing::Asteroid;

        sectorFieldThings[index] = sectorFieldThings[columnCount - usedFieldsCount - 1];

        usedFieldsCount++;
    }

    for (unsigned int i = 0; i < scanSector.encounters; ++i)
    {
        auto index = randomNumberGenerator->GenerateBetweenInclusive(0, columnCount - usedFieldsCount - 1);

        *sectorFieldThings[index] = domain::models::SectorFieldThing::Encounter;

        sectorFieldThings[index] = sectorFieldThings[columnCount - usedFieldsCount - 1];

        usedFieldsCount++;
    }

    for (unsigned int i = 0; i < scanSector.planets; ++i)
    {
        auto index = randomNumberGenerator->GenerateBetweenInclusive(0, columnCount - usedFieldsCount - 1);

        *sectorFieldThings[index] = domain::models::SectorFieldThing::Planet;

        sectorFieldThings[index] = sectorFieldThings[columnCount - usedFieldsCount - 1];

        usedFieldsCount++;
    }

    return sector;
}
