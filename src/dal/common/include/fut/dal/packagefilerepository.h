#ifndef FUTURAMA_FUT_DAL_PACKAGEFILEREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_PACKAGEFILEREPOSITORY_H_INCLUDED

#include <fut/domain/models/package.h>
#include <fut/infra/csvparser.h>
#include <fut/infra/randomnumbergenerator.h>

#include "fut/dal/packagerepository.h"

namespace fut::dal
{
class PackageFileRepository : public PackageRepository
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

    unsigned int packageCount;
    domain::models::Package packages[64];

  public:
    PackageFileRepository(infra::RandomNumberGenerator& randomNumberGenerator);

    void ReadPackagesFromCsv(const char* filePath);

    domain::models::Package GetRandomPackage() const override;
}; // class PackageFileRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_PACKAGEFILEREPOSITORY_H_INCLUDED
