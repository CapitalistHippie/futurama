#ifndef FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED

#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerStopped : public StateHandlerBase
{
  private:
    void StartCommandHandler() const;
    void GameStartedEventHandler() const;

    void ExitStateBase() noexcept override;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerStopped
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED
