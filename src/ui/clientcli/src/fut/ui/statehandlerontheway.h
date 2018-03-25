#ifndef FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED

#include <fut/domain/events/statechanged.h>

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
    void ExamineCommandHandler() const;
    void DeliverCommandHandler() const;
    void SkipCommandHandler() const;

    void MovedToSectorGameEventHandler() const;
    void MovedToFieldGameEventHandler() const;
    void MovedToHeadquartersGameEventHandler() const;
    void PackagePickedUpGameEventHandler() const;
    void StateChangedGameEventHandler(const domain::events::StateChanged& evt) const;
    void EncountersMovedGameEventHandler() const;

    void PrintCliWithPackageInfo() const;
    void PrintCli(const char* extra = nullptr) const;
    void PrintSector() const;
    void PrintPackageInfo() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerOnTheWay
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED
