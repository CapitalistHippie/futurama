#ifndef FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTER_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTER_H_INCLUDED

#include "fut/domain/models/character.h"
#include "fut/domain/models/encounterconsequence.h"

namespace fut::domain::models
{
struct Encounter
{
    char description[256] = "";

    domain::models::EncounterConsequence fryConsequence;
    unsigned int fryDamageMin = 0;
    unsigned int fryDamageMax = 0;

    char leelaNegotiationText[256] = "";
    domain::models::EncounterConsequence leelaNegotiationConsequence;
    unsigned int leelaDamageMin = 0;
    unsigned int leelaDamageMax = 0;
    int leelaVictoryPoints = 0;

    char benderSuccessText[256] = "";
    domain::models::EncounterConsequence benderSuccessConsequence;
    unsigned int benderSuccessDamageMin = 0;
    unsigned int benderSuccessDamageMax = 0;
    int benderSuccessVictoryPoints = 0;

    char benderFailureText[256] = "";
    domain::models::EncounterConsequence benderFailureConsequence;
    unsigned int benderFailureDamageMin = 0;
    unsigned int benderFailureDamageMax = 0;
    int benderFailureVictoryPoints = 0;
}; // struct Encounter
} // namespace fut::domain::models

#endif // #ifndef FUTURAMA_FUT_DOMAIN_MODELS_ENCOUNTER_H_INCLUDED
