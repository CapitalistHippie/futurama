#ifndef FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED

#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerInEncounter : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void ContinueCommandHandler() const;
    void ShipRepairedGameEventHandler() const;

    void PrintCli(const char* extra = nullptr) const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerInEncounter
} // namespace fut::ui

#endif // #ifndef FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED
