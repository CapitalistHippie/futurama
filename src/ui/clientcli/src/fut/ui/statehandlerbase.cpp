#include "fut/ui/statehandlerbase.h"

using namespace fut;
using namespace fut::ui;

StateHandlerBase::StateHandlerBase(ClientCli& context,
                                   app::Client& client,
                                   infra::Subject& commandSubject,
                                   std::ostream& outputStream)
  : context(&context)
  , client(&client)
  , commandSubject(&commandSubject)
  , outputStream(&outputStream)
{
}

void StateHandlerBase::ExitState() noexcept
{
    ExitStateBase();
}
