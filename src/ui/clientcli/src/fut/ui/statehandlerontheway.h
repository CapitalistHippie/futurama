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
    bool showPackageInfo = false;

    void ExitStateBase() noexcept override;

    void MoveCommandHandler(const Command& command);
    void PickupCommandHandler();
    void ExamineCommandHandler();
    void DeliverCommandHandler();
    void SkipCommandHandler();

    void MovedToSectorGameEventHandler();
    void MovedToFieldGameEventHandler();
    void MovedToHeadquartersGameEventHandler() const;
    void PackagePickedUpGameEventHandler();
    void StateChangedGameEventHandler(const domain::events::StateChanged& evt) const;
    void EncountersMovedGameEventHandler();

    void PrintCli(const char* extra = nullptr);
    void PrintSector() const;
    void PrintPackageInfo() const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerOnTheWay
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERONTHEWAY_H_INCLUDED
