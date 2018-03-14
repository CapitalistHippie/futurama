#include "fut/app/scangenerator.h"

using namespace fut;
using namespace fut::app;

ScanGenerator::ScanGenerator(infra::RandomNumberGenerator& randomNumberGenerator)
  : randomNumberGenerator(&randomNumberGenerator)
{
}

domain::models::Scan ScanGenerator::GenerateScan() const
{
    domain::models::Scan scan;

    for (unsigned int i = 0; i < 5; ++i)
    {
        for (unsigned int ii = 0; ii < 5; ++ii)
        {
            scan.sectors[i][ii].asteroids = randomNumberGenerator->GenerateBetweenInclusive(0, 9);
            scan.sectors[i][ii].meetings = randomNumberGenerator->GenerateBetweenInclusive(0, 3);
            scan.sectors[i][ii].planets = randomNumberGenerator->GenerateBetweenInclusive(0, 2);
        }
    }

    return scan;
}
