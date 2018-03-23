#include "fut/dal/meetingfilerepository.h"

using namespace fut;
using namespace fut::dal;

void MeetingFileRepository::ParseDamage(const char* text,
                                        unsigned int& damageMinBuffer,
                                        unsigned int& damageMaxBuffer) const
{
    char* endptr;

    damageMinBuffer = strtol(text + 1, &endptr, 10);
    damageMaxBuffer = strtol(endptr + 1, &endptr, 10);
}

void MeetingFileRepository::ParseVictoryPoints(const char* text, unsigned int& victoryPointsBuffer) const
{
    char* endptr;

    victoryPointsBuffer = strtol(text + 4, &endptr, 10);
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

        char fryConsequenceBuffer[64] = "";
        row.ParseNextColumn(fryConsequenceBuffer, sizeof(fryConsequenceBuffer));

        if (strcmp(fryConsequenceBuffer, "[0]") == 0)
        {
            meeting.fryConsequence = domain::models::MeetingConsequence::Nothing;
        }
        else
        {
            meeting.fryConsequence = domain::models::MeetingConsequence::Battle;
            ParseDamage(fryConsequenceBuffer, meeting.fryDamageMin, meeting.fryDamageMax);
        }

        row.ParseNextColumn(meeting.leelaNegotiationText, sizeof(meeting.leelaNegotiationText));

        char leelaConsequenceBuffer[64] = "";
        row.ParseNextColumn(leelaConsequenceBuffer, sizeof(leelaConsequenceBuffer));

        if (strcmp(leelaConsequenceBuffer, "[0]") == 0)
        {
            meeting.leelaNegotiationConsequence = domain::models::MeetingConsequence::Nothing;
        }
        else if (strcmp(leelaConsequenceBuffer, "[repair]") == 0)
        {
            meeting.leelaNegotiationConsequence = domain::models::MeetingConsequence::Repair;
        }
        else if (leelaConsequenceBuffer[1] == 'v')
        {
            meeting.leelaNegotiationConsequence = domain::models::MeetingConsequence::VictoryPoints;
            ParseVictoryPoints(leelaConsequenceBuffer, meeting.leelaVictoryPoints);
        }
        else
        {
            meeting.leelaNegotiationConsequence = domain::models::MeetingConsequence::Battle;
            ParseDamage(leelaConsequenceBuffer, meeting.leelaDamageMin, meeting.leelaDamageMax);
        }
    }
}

domain::models::Meeting MeetingFileRepository::GetRandomMeeting() const
{
    return meetings[randomNumberGenerator->GenerateBetweenInclusive(0, meetingCount - 1)];
}
