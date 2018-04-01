#include "fut/dal/encounterfilerepository.h"

using namespace fut;
using namespace fut::dal;

void EncounterFileRepository::ParseConsequence(const char* consequenceText,
                                               domain::models::EncounterConsequence& consequenceBuffer,
                                               unsigned int& damageMinBuffer,
                                               unsigned int& damageMaxBuffer,
                                               int& victoryPointsBuffer)
{
    if (strcmp(consequenceText, "[0]") == 0)
    {
        consequenceBuffer = domain::models::EncounterConsequence::Nothing;
    }
    else if (strcmp(consequenceText, "[repair]") == 0)
    {
        consequenceBuffer = domain::models::EncounterConsequence::Repair;
    }
    else if (consequenceText[1] == 'v')
    {
        consequenceBuffer = domain::models::EncounterConsequence::VictoryPoints;
        ParseVictoryPoints(consequenceText, victoryPointsBuffer);
    }
    else
    {
        consequenceBuffer = domain::models::EncounterConsequence::Battle;
        ParseDamage(consequenceText, damageMinBuffer, damageMaxBuffer);
    }
}

void EncounterFileRepository::ParseDamage(const char* text,
                                          unsigned int& damageMinBuffer,
                                          unsigned int& damageMaxBuffer) const
{
    char* endptr;

    damageMinBuffer = strtol(text + 1, &endptr, 10);
    damageMaxBuffer = strtol(endptr + 1, &endptr, 10);
}

void EncounterFileRepository::ParseVictoryPoints(const char* text, int& victoryPointsBuffer) const
{
    char* endptr;

    victoryPointsBuffer = strtol(text + 3, &endptr, 10);
}

EncounterFileRepository::EncounterFileRepository(infra::RandomNumberGenerator& randomNumberGenerator)
  : encounterCount(0)
  , randomNumberGenerator(&randomNumberGenerator)
{
}

void EncounterFileRepository::ReadEncountersFromCsv(const char* filePath)
{
    infra::CsvParser parser;
    parser.OpenFile(filePath);

    infra::CsvRow row;

    while (parser.ParseNextRow(row) != infra::ParsingStatus::EndOfFile)
    {
        domain::models::Encounter& encounter = encounters[encounterCount++];

        row.ParseNextColumn(encounter.description, sizeof(encounter.description));

        // Fry.
        char columnBuffer[256] = "";
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        if (strcmp(columnBuffer, "[0]") == 0)
        {
            encounter.fryConsequence = domain::models::EncounterConsequence::Nothing;
        }
        else
        {
            encounter.fryConsequence = domain::models::EncounterConsequence::Battle;
            ParseDamage(columnBuffer, encounter.fryDamageMin, encounter.fryDamageMax);
        }

        // Leela.
        row.ParseNextColumn(encounter.leelaNegotiationText, sizeof(encounter.leelaNegotiationText));

        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        ParseConsequence(columnBuffer,
                         encounter.leelaNegotiationConsequence,
                         encounter.leelaDamageMin,
                         encounter.leelaDamageMax,
                         encounter.leelaVictoryPoints);

        // Bender failure.
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        char* consequenceLoc = strchr(columnBuffer, '[');

        if (consequenceLoc != nullptr)
        {
            // If there's a consequence. Parse it.
            ParseConsequence(consequenceLoc,
                             encounter.benderFailureConsequence,
                             encounter.benderFailureDamageMin,
                             encounter.benderFailureDamageMax,
                             encounter.benderFailureVictoryPoints);

            // Copy the text if there is any.
            if (consequenceLoc != columnBuffer)
            {
                strncpy(encounter.benderFailureText, columnBuffer, consequenceLoc - columnBuffer);
            }
        }
        else
        {
            // No consequence. Just text. Copy it.
            encounter.benderFailureConsequence = domain::models::EncounterConsequence::Nothing;
            strcpy(encounter.benderFailureText, columnBuffer);
        }

        // Bender success.
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        consequenceLoc = strchr(columnBuffer, '[');

        if (consequenceLoc != nullptr)
        {
            // If there's a consequence. Parse it.
            ParseConsequence(consequenceLoc,
                             encounter.benderSuccessConsequence,
                             encounter.benderSuccessDamageMin,
                             encounter.benderSuccessDamageMax,
                             encounter.benderSuccessVictoryPoints);

            // Copy the text if there is any.
            if (consequenceLoc != columnBuffer)
            {
                strncpy(encounter.benderSuccessText, columnBuffer, consequenceLoc - columnBuffer);
            }
        }
        else
        {
            // No consequence. Just text. Copy it.
            encounter.benderSuccessConsequence = domain::models::EncounterConsequence::Nothing;
            strcpy(encounter.benderSuccessText, columnBuffer);
        }
    }
}

domain::models::Encounter EncounterFileRepository::GetRandomEncounter() const
{
    return encounters[randomNumberGenerator->GenerateBetweenInclusive(0, encounterCount - 1)];
}
