#ifndef FUTURAMA_FUT_UI_STATEHANDLERPICKINGENCOUNTERNEGOTIATOR_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERPICKINGENCOUNTERNEGOTIATOR_H_INCLUDED

#include "fut/ui/command.h"
#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerPickingEncounterNegotiator : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void PickCommandHandler(const Command& command) const;
    void EncounterStartedGameEventHandler() const;

    void PrintCli(const char* extra = nullptr) const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerPickingEncounterNegotiator
} // namespace fut::ui

#endif // #ifndef FUTURAMA_FUT_UI_STATEHANDLERPICKINGENCOUNTERNEGOTIATOR_H_INCLUDED
