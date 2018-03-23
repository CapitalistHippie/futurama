#ifndef FUTURAMA_FUT_DOMAIN_MODELS_MEETING_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_MEETING_H_INCLUDED

#include "fut/domain/models/meetingconsequence.h"
#include "fut/domain/models/meetingnegotiator.h"

namespace fut::domain::models
{
struct Meeting
{
    char description[64] = "";

    MeetingNegotiator negotiator;

    domain::models::MeetingConsequence fryConsequence;
    unsigned int fryDamageMin = 0;
    unsigned int fryDamageMax = 0;

    char leelaNegotiationText[64] = "";
    domain::models::MeetingConsequence leelaNegotiationConsequence;
    unsigned int leelaDamageMin = 0;
    unsigned int leelaDamageMax = 0;
    unsigned int leelaVictoryPoints = 0;

    domain::models::MeetingConsequence benderSuccessConsequence;
    domain::models::MeetingConsequence benderFailureConsequence;
}; // struct Meeting
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_MEETING_H_INCLUDED
