#ifndef FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED

#include "fut/ui/statehandlerbase.h"

#include <fut/domain/events/enemyhit.h>
#include <fut/domain/events/enemymissed.h>
#include <fut/domain/events/shipdamaged.h>

namespace fut::ui
{
class StateHandlerInEncounter : public StateHandlerBase
{
  private:
    void ExitStateBase() noexcept override;

    void ContinueCommandHandler() const;
    void ShipRepairedGameEventHandler() const;
    void ShipDamagedGameEventHandler(const domain::events::ShipDamaged& evt) const;
    void EnemyHitGameEventHandler(const domain::events::EnemyHit& evt) const;
    void EnemyMissedGameEventHandler(const domain::events::EnemyMissed& evt) const;

    void PrintCli(const char* extra = nullptr) const;

  public:
    using StateHandlerBase::StateHandlerBase;

    void EnterState() override;
}; // class StateHandlerInEncounter
} // namespace fut::ui

#endif // #ifndef FUTURAMA_FUT_UI_STATEHANDLERINENCOUNTER_H_INCLUDED
