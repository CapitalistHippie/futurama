#ifndef FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED

#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerMenu : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void StartCommandHandler() const;

    void PrintCli() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerMenu
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERSTOPPED_H_INCLUDED
