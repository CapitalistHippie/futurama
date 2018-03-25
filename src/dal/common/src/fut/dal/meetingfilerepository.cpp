#include "fut/dal/meetingfilerepository.h"

using namespace fut;
using namespace fut::dal;

void MeetingFileRepository::ParseConsequence(const char* consequenceText,
                                             domain::models::MeetingConsequence& consequenceBuffer,
                                             unsigned int& damageMinBuffer,
                                             unsigned int& damageMaxBuffer,
                                             int& victoryPointsBuffer)
{
    if (strcmp(consequenceText, "[0]") == 0)
    {
        consequenceBuffer = domain::models::MeetingConsequence::Nothing;
    }
    else if (strcmp(consequenceText, "[repair]") == 0)
    {
        consequenceBuffer = domain::models::MeetingConsequence::Repair;
    }
    else if (consequenceText[1] == 'v')
    {
        consequenceBuffer = domain::models::MeetingConsequence::VictoryPoints;
        ParseVictoryPoints(consequenceText, victoryPointsBuffer);
    }
    else
    {
        consequenceBuffer = domain::models::MeetingConsequence::Battle;
        ParseDamage(consequenceText, damageMinBuffer, damageMaxBuffer);
    }
}

void MeetingFileRepository::ParseDamage(const char* text,
                                        unsigned int& damageMinBuffer,
                                        unsigned int& damageMaxBuffer) const
{
    char* endptr;

    damageMinBuffer = strtol(text + 1, &endptr, 10);
    damageMaxBuffer = strtol(endptr + 1, &endptr, 10);
}

void MeetingFileRepository::ParseVictoryPoints(const char* text, int& victoryPointsBuffer) const
{
    char* endptr;

    victoryPointsBuffer = strtol(text + 3, &endptr, 10);
}

MeetingFileRepository::MeetingFileRepository(infra::RandomNumberGenerator& randomNumberGenerator)
  : meetingCount(0)
  , randomNumberGenerator(&randomNumberGenerator)
{
}

void MeetingFileRepository::ReadMeetingsFromCsv(const char* filePath)
{
    infra::CsvParser parser;
    parser.OpenFile(filePath);

    infra::CsvRow row;

    while (parser.ParseNextRow(row) != infra::ParsingStatus::EndOfFile)
    {
        domain::models::Meeting& meeting = meetings[meetingCount++];

        row.ParseNextColumn(meeting.description, sizeof(meeting.description));

        // Fry.
        char columnBuffer[64] = "";
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        if (strcmp(columnBuffer, "[0]") == 0)
        {
            meeting.fryConsequence = domain::models::MeetingConsequence::Nothing;
        }
        else
        {
            meeting.fryConsequence = domain::models::MeetingConsequence::Battle;
            ParseDamage(columnBuffer, meeting.fryDamageMin, meeting.fryDamageMax);
        }

        // Leela.
        row.ParseNextColumn(meeting.leelaNegotiationText, sizeof(meeting.leelaNegotiationText));

        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        ParseConsequence(columnBuffer,
                         meeting.leelaNegotiationConsequence,
                         meeting.leelaDamageMin,
                         meeting.leelaDamageMax,
                         meeting.leelaVictoryPoints);

        // Bender failure.
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        char* consequenceLoc = strchr(columnBuffer, '[');

        if (consequenceLoc != nullptr)
        {
            // If there's a consequence. Parse it.
            ParseConsequence(consequenceLoc,
                             meeting.benderFailureConsequence,
                             meeting.benderFailureDamageMin,
                             meeting.benderFailureDamageMax,
                             meeting.benderFailureVictoryPoints);

            // Copy the text if there is any.
            if (consequenceLoc != columnBuffer)
            {
                strncpy(meeting.benderFailureText, columnBuffer, consequenceLoc - columnBuffer);
            }
        }
        else
        {
            // No consequence. Just text. Copy it.
            meeting.benderFailureConsequence = domain::models::MeetingConsequence::Nothing;
            strcpy(meeting.benderFailureText, columnBuffer);
        }

        // Bender success.
        row.ParseNextColumn(columnBuffer, sizeof(columnBuffer));

        consequenceLoc = strchr(columnBuffer, '[');

        if (consequenceLoc != nullptr)
        {
            // If there's a consequence. Parse it.
            ParseConsequence(consequenceLoc,
                             meeting.benderSuccessConsequence,
                             meeting.benderSuccessDamageMin,
                             meeting.benderSuccessDamageMax,
                             meeting.benderSuccessVictoryPoints);

            // Copy the text if there is any.
            if (consequenceLoc != columnBuffer)
            {
                strncpy(meeting.benderSuccessText, columnBuffer, consequenceLoc - columnBuffer);
            }
        }
        else
        {
            // No consequence. Just text. Copy it.
            meeting.benderSuccessConsequence = domain::models::MeetingConsequence::Nothing;
            strcpy(meeting.benderSuccessText, columnBuffer);
        }
    }
}

domain::models::Meeting MeetingFileRepository::GetRandomMeeting() const
{
    return meetings[randomNumberGenerator->GenerateBetweenInclusive(0, meetingCount - 1)];
}
