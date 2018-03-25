#ifndef FUTURAMA_FUT_UI_STATEHANDLERPICKINGMEETINGCHARACTER_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERPICKINGMEETINGCHARACTER_H_INCLUDED

#include <fut/domain/events/statechanged.h>

#include "fut/ui/command.h"
#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerPickingMeetingCharacter : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void PickCommandHandler(const Command& command) const;
    void StateChangedGameEventHandler(const domain::events::StateChanged& evt) const;

    void PrintCli(const char* extra = nullptr) const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerPickingMeetingCharacter
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERPICKINGMEETINGCHARACTER_H_INCLUDED
