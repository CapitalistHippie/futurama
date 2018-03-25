#ifndef FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTERINSTANCE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTERINSTANCE_H_INCLUDED

#include "fut/domain/models/character.h"
#include "fut/domain/models/encounterconsequence.h"

namespace fut::domain::models
{
struct EncounterInstance
{
    char description[256] = "";

    Character negotiator;
    domain::models::EncounterConsequence consequence;
    char consequenceText[256] = "";
    unsigned int damageMin = 0;
    unsigned int damageMax = 0;
    int victoryPoints = 0;

    unsigned int enemyHitCount = 0;
}; // struct EncounterInstance
} // namespace fut::domain::models

#endif // #ifndef FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTERINSTANCE_H_INCLUDED
