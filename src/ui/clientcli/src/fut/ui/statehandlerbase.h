#ifndef FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED

#include <ostream>
#include <utility>

#include <fut/app/client.h>
#include <fut/infra/subject.h>

#include "fut/ui/clientcli.h"
#include "fut/ui/command.h"
#include "fut/ui/statehandler.h"

namespace fut::ui
{
class StateHandlerBase : public StateHandler
{
  private:
    virtual void ExitStateBase() noexcept = 0;

    infra::Subject::ObserverHandle commandObserverHandles[infra::Subject::ObserverCount];
    unsigned int commandObserverHandlesIndex;

    infra::Subject::ObserverHandle gameEventObserverHandles[infra::Subject::ObserverCount];
    unsigned int gameEventObserverHandlesIndex;

  protected:
    ClientCli* context;
    app::Client* client;
    infra::Subject* commandsSubject;
    std::ostream* outputStream;

    template<typename TObserver>
    void RegisterCommandObserver(const char* commandName, TObserver&& observer)
    {
        auto observerHandle = commandsSubject->RegisterPredicateObserver<Command>(
          [commandName](const Command& command) { return strcmp(command.name, commandName) == 0; },
          std::forward<TObserver>(observer));

        commandObserverHandles[commandObserverHandlesIndex++] = observerHandle;
    }

    template<typename TObservable, typename TObserver>
    void RegisterGameEventObserver(TObserver&& observer)
    {
        auto observerHandle =
          client->GetGameEventsSubject().RegisterSimpleObserver<TObservable>(std::forward<TObserver>(observer));

        gameEventObserverHandles[gameEventObserverHandlesIndex++] = observerHandle;
    }

  public:
    StateHandlerBase(ClientCli& context,
                     app::Client& client,
                     infra::Subject& commandsSubject,
                     std::ostream& outputStream);
    ~StateHandlerBase() noexcept = default;

    void ExitState() noexcept override;
}; // class StateHandlerBase
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED
