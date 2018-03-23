#ifndef FUTURAMA_FUT_DAL_MEETINGREPOSITORY_H_INCLUDED
#define FUTURAMA_FUT_DAL_MEETINGREPOSITORY_H_INCLUDED

#include <fut/domain/models/meeting.h>

namespace fut::dal
{
class MeetingRepository
{
  public:
    virtual ~MeetingRepository() noexcept = default;

    virtual domain::models::Meeting GetRandomMeeting() const = 0;
}; // class PackageRepository
} // namespace fut::dal

#endif // #ifndef FUTURAMA_FUT_DAL_MEETINGREPOSITORY_H_INCLUDED
