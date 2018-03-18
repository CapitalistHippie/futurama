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

    void MoveCommandHandler(const Command& command) const;
    void PickupCommandHandler() const;
    void MovedToSectorGameEventHandler() const;
    void MovedToFieldGameEventHandler() const;
    void MovedToHeadquartersGameEventHandler() const;

    void PrintCli(const char* extra = nullptr) const;
    void PrintSector() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerOnTheWay
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED
