#include "fut/ui/statehandlerbase.h"

using namespace fut;
using namespace fut::ui;

StateHandlerBase::StateHandlerBase(ClientCli& context,
                                   app::Client& client,
                                   infra::Subject& commandsSubject,
                                   std::ostream& outputStream)
  : commandObserverHandlesIndex(0)
  , eventObserverHandlesIndex(0)
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

    for (unsigned int i = 0; i < eventObserverHandlesIndex; ++i)
    {
        client->eventsSubject.UnregisterSimpleObserver(eventObserverHandles[i]);
    }

    ExitStateBase();
}
