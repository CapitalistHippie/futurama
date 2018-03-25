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
    int leelaVictoryPoints = 0;

    char benderSuccessText[64] = "";
    domain::models::MeetingConsequence benderSuccessConsequence;
    unsigned int benderSuccessDamageMin = 0;
    unsigned int benderSuccessDamageMax = 0;
    int benderSuccessVictoryPoints = 0;

    char benderFailureText[64] = "";
    domain::models::MeetingConsequence benderFailureConsequence;
    unsigned int benderFailureDamageMin = 0;
    unsigned int benderFailureDamageMax = 0;
    int benderFailureVictoryPoints = 0;
}; // struct Meeting
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_MEETING_H_INCLUDED
