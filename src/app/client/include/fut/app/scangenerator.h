#ifndef FUTURAMA_FUT_APP_SCANGENERATOR_H_INCLUDED
#define FUTURAMA_FUT_APP_SCANGENERATOR_H_INCLUDED

#include <fut/domain/models/scan.h>
#include <fut/domain/models/scansector.h>
#include <fut/infra/randomnumbergenerator.h>

namespace fut::app
{
class ScanGenerator
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

  public:
    ScanGenerator(infra::RandomNumberGenerator& randomNumberGenerator);

    domain::models::Scan GenerateScan() const;
}; // class ScanGenerator
} // namespace fut::app

#endif // FUTURAMA_FUT_APP_SCANGENERATOR_H_INCLUDED
