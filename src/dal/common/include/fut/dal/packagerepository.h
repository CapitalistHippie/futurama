#ifndef FUTURAMA_FUT_DAL_PACKAGEREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_PACKAGEREPOSITORY_H_INCLUDED

#include <fut/domain/models/package.h>

namespace fut::dal
{
class PackageRepository
{
  public:
    virtual ~PackageRepository() noexcept = default;

    virtual domain::models::Package GetRandomPackage() const = 0;
}; // class PackageRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_PACKAGEREPOSITORY_H_INCLUDED
