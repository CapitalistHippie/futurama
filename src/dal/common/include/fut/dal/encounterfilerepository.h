#ifndef FUTURAMA_FUT_DAL_ENCOUNTERFILEREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_ENCOUNTERFILEREPOSITORY_H_INCLUDED

#include <fut/domain/models/encounter.h>
#include <fut/domain/models/encounterconsequence.h>
#include <fut/infra/csvparser.h>
#include <fut/infra/randomnumbergenerator.h>

#include "fut/dal/encounterrepository.h"

namespace fut::dal
{
class EncounterFileRepository : public EncounterRepository
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

    unsigned int encounterCount;
    domain::models::Encounter encounters[64];

    void ParseConsequence(const char* consequenceText,
                          domain::models::EncounterConsequence& consequenceBuffer,
                          unsigned int& damageMinBuffer,
                          unsigned int& damageMaxBuffer,
                          int& victoryPointsBuffer);
    void ParseDamage(const char* text, unsigned int& damageMinBuffer, unsigned int& damageMaxBuffer) const;
    void ParseVictoryPoints(const char* text, int& victoryPointsBuffer) const;

  public:
    EncounterFileRepository(infra::RandomNumberGenerator& randomNumberGenerator);

    void ReadEncountersFromCsv(const char* filePath);

    domain::models::Encounter GetRandomEncounter() const override;
}; // class EncounterFileRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_ENCOUNTERFILEREPOSITORY_H_INCLUDED
