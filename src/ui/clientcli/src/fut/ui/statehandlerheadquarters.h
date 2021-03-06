#ifndef FUTURAMA_FUT_UI_STATEHANDLERHEADQUARTERS_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERHEADQUARTERS_H_INCLUDED

#include "fut/ui/command.h"
#include "fut/ui/statehandlerbase.h"

namespace fut::ui
{
class StateHandlerHeadquarters : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void SectorCommandHandler(const Command& command) const;
    void MovedToSectorGameEventHandler() const;

    void PrintCli(const char* extra = nullptr) const;
    void PrintScan() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerHeadquarters
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERHEADQUARTERS_H_INCLUDED
