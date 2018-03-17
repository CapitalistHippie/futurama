#ifndef FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED

#include "fut/ui/command.h"
#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerOnTheWay : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void MovedToSectorGameEventHandler() const;

    void PrintCli(const char* extra) const;
    void PrintSector() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerOnTheWay
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED