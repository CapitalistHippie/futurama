#include "fut/ui/statehandlerbase.h"

using namespace fut;
using namespace fut::ui;

StateHandlerBase::StateHandlerBase(ClientCli& context,
                                   app::Client& client,
                                   infra::Subject& commandsSubject,
                                   std::ostream& outputStream)
  : commandObserverHandlesIndex(0)
  , gameEventObserverHandlesIndex(0)
  , context(&context)
  , client(&client)
  , commandsSubject(&commandsSubject)
  , outputStream(&outputStream)
{
}

void StateHandlerBase::ExitState() noexcept
{
    for (unsigned int i = 0; i < commandObserverHandlesIndex; ++i)
    {
        commandsSubject->UnregisterPredicateObserver(commandObserverHandles[i]);
    }

    for (unsigned int i = 0; i < gameEventObserverHandlesIndex; ++i)
    {
        client->GetGameEventsSubject().UnregisterSimpleObserver(gameEventObserverHandles[i]);
    }

    ExitStateBase();
}
