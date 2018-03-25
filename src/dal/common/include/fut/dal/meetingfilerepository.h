#ifndef FUTURAMA_FUT_DAL_MEETINGFILEREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_MEETINGFILEREPOSITORY_H_INCLUDED

#include <fut/domain/models/meeting.h>
#include <fut/infra/csvparser.h>
#include <fut/infra/randomnumbergenerator.h>

#include "fut/dal/meetingrepository.h"

namespace fut::dal
{
class MeetingFileRepository : public MeetingRepository
{
  private:
    infra::RandomNumberGenerator* randomNumberGenerator;

    unsigned int meetingCount;
    domain::models::Meeting meetings[64];

    void ParseConsequence(const char* consequenceText,
                          domain::models::MeetingConsequence& consequenceBuffer,
                          unsigned int& damageMinBuffer,
                          unsigned int& damageMaxBuffer,
                          int& victoryPointsBuffer);
    void ParseDamage(const char* text, unsigned int& damageMinBuffer, unsigned int& damageMaxBuffer) const;
    void ParseVictoryPoints(const char* text, int& victoryPointsBuffer) const;

  public:
    MeetingFileRepository(infra::RandomNumberGenerator& randomNumberGenerator);

    void ReadMeetingsFromCsv(const char* filePath);

    domain::models::Meeting GetRandomMeeting() const override;
}; // class MeetingFileRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_MEETINGFILEREPOSITORY_H_INCLUDED
