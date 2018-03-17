#ifndef FUTURAMA_FUT_APP_SECTORGENERATOR_H_INCLUDED
#define FUTURAMA_FUT_APP_SECTORGENERATOR_H_INCLUDED

#include <fut/domain/models/scansector.h>
#include <fut/domain/models/sector.h>
#include <fut/infra/randomnumbergenerator.h>

namespace fut::app
{
class SectorGenerator
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

  public:
    SectorGenerator(infra::RandomNumberGenerator& randomNumberGenerator);

    domain::models::Sector GenerateSector(const domain::models::ScanSector& scanSector) const;
}; // class ScanGenerator
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_SECTORGENERATOR_H_INCLUDED
