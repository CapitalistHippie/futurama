#ifndef FUTURAMA_FUT_DAL_ENCOUNTERREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_ENCOUNTERREPOSITORY_H_INCLUDED

#include <fut/domain/models/encounter.h>

namespace fut::dal
{
class EncounterRepository
{
  public:
    virtual ~EncounterRepository() noexcept = default;

    virtual domain::models::Encounter GetRandomEncounter() const = 0;
}; // class EncounterRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_ENCOUNTERREPOSITORY_H_INCLUDED
