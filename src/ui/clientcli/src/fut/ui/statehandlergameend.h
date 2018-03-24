#ifndef FUTURAMA_FUT_UI_STATEHANDLERGAMEEND_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERGAMEEND_H_INCLUDED

#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerGameEnd : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void MenuCommandHandler() const;

    void PrintCli() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerGameEnd
} // namespace fut::ui

#endif // #ifndef FUTURAMA_FUT_UI_STATEHANDLERGAMEEND_H_INCLUDED
